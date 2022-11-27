from points import *
from misc import *
from constants import *

def Fw(i):
    xvw1 = (xvs[i]+xvs[(i+1)%N])/2
    yvw1 = (yvs[i]+yvs[(i+1)%N])/2
    xvw2 = (xvs[i]+xvs[(i-1)%N])/2
    yvw2 = (yvs[i]+yvs[(i-1)%N])/2
    vw1 = sqrt(xvw1**2+yvw1**2)
    vw2 = sqrt(xvw2**2+yvw2**2)
    d1 = dist(i,(i+1)%N)
    d2 = dist(i,(i-1)%N)
    xn1 = (xs[(i+1)%N]-xs[i])/d1
    yn1 = (ys[(i+1)%N]-ys[i])/d1
    xn2 = (xs[(i-1)%N]-xs[i])/d2
    yn2 = (ys[(i-1)%N]-ys[i])/d2
    in_vec = pressure_vecs[i]
    if in_vec[0]*xvw1+in_vec[1]*yvw1 > 0:
        ro1 = 0
    else:
        ro1 = P/(287*temp)
    if in_vec[0]*xvw2+in_vec[1]*yvw2 > 0:
        ro2 = 0
    else:
        ro2 = P/(287*temp)
    fw1 = Cf*ro1*vw1/2*L*abs(xn1*yvw1-yn1*xvw1)*d1
    fw2 = Cf*ro2*vw2/2*L*abs(xn2*yvw2-yn2*xvw2)*d2

    xfw1 = -xvw1*fw1
    yfw1 = -yvw1*fw1
    if vw1 != 0:
        xfw1 /= vw1
        yfw1 /= vw1
    xfw2 = -xvw2*fw2
    yfw2 = -yvw2*fw2
    if vw2 != 0:
        xfw2 /= vw2
        yfw2 /= vw2

    xfw = xfw1+xfw2
    yfw = yfw1+yfw2

    cosv1 = xn1*xvw1+yn1*yvw1
    cosv2 = xn2*xvw2+yn2*yvw2
    fwv1 = abs(cf*cosv1*L*d1*ro1*vw1/4)
    fwv2 = abs(cf*cosv2*L*d2*ro2*vw2/4)
    xfwv1 = -fwv1*(xn1*cosv1)
    yfwv1 = -fwv1*(yn1*cosv1)
    if vw1 != 0:
        xfwv1 /= vw1
        yfwv1 /= vw1
    xfwv2 = -fwv2*(xn2*cosv2)
    yfwv2 = -fwv2*(yn2*cosv2)
    if vw2 != 0:
        xfwv2 /= vw2
        yfwv2 /= vw2
    
    xfw += xfwv1+xfwv2
    yfw += yfwv1+yfwv2

    return (xfw,yfw)

def find_T():
    global Ts
    for i,fr in enumerate(free_str):
        if fr[0]:
            Ts[i] = k*(dist(i,(i+1)%N)-l0)
        else:
            #Tss[i] = Ts[fr[1]]
            Ts[i] = k_crit*(dist(i,(i+1)%N)-l0)


def xv1_eq(i,tension=True):
    fp = P*L*(dist(i,(i+1)%N)+dist(i,(i-1)%N))/2*pressure_vecs[i][0]
    fw = Fw(i)[0]
    xn1 = (xs[(i+1)%N]-xs[i])/dist(i,(i+1)%N)
    xn2 = (xs[(i-1)%N]-xs[i])/dist(i,(i-1)%N)
    ft1 = Ts[i]*xn1
    ft2 = Ts[(i-1)%N]*xn2
    ft = 0
    if tension:
        if abs(xvs[i]) > eps:
            direct = abs(xvs[i])/xvs[i]
            if ys[i] < eps:
                yf = m*yv1_eq(i,tension=False)
                ft = -direct*mu*max(0,-yf)
            elif ys[i] > box_h-eps:
                yf = m*yv1_eq(i,tension=False)
                ft = -direct*mu*max(0,yf)

    return (fp+fw+ft1+ft2+ft)/m
            

def yv1_eq(i,tension=True):
    fm = -m*g
    fp = P*L*(dist(i,(i+1)%N)+dist(i,(i-1)%N))/2*pressure_vecs[i][1]
    fw = Fw(i)[1]
    yn1 = (ys[(i+1)%N]-ys[i])/dist(i,(i+1)%N)
    yn2 = (ys[(i-1)%N]-ys[i])/dist(i,(i-1)%N)
    ft1 = Ts[i]*yn1
    ft2 = Ts[(i-1)%N]*yn2
    ft = 0
    if tension:
        if abs(yvs[i]) > eps:
            direct = abs(yvs[i])/yvs[i]
            if ys[i] < eps:
                xf = m*xv1_eq(i,tension=False)
                ft = -direct*mu*max(0,-xf)
            elif ys[i] > box_w-eps:
                xf = m*xv1_eq(i,tension=False)
                ft = -direct*mu*max(0,xf)

    return (fp+fw+ft1+ft2+ft+fm)/m

def y1_eq(i):
    if ys[i] < eps:
        return max(yvs[i],0)
    elif ys[i] > box_h-eps:
        return min(yvs[i],0)
    else:
        return yvs[i]

def x1_eq(i):
    if xs[i] < eps:
        return max(xvs[i],0)
    elif xs[i] > box_w-eps:
        return min(xvs[i],0)
    else:
        return xvs[i]