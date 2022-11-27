import numpy as np
from constants import *
from math import *
from points import *

def get_tension_colors():
    res = []
    for ts in Ts:
        ts = abs(ts)
        if ts < HIGH_TENSION:
            r = 0
            g = min(ts/HIGH_TENSION,1)
            b = max(1-ts/HIGH_TENSION,0)
        else:
            r = min((ts-HIGH_TENSION)/HIGH_TENSION,1)
            g = max(1-(ts-HIGH_TENSION)/HIGH_TENSION,0)
            b = 0
        
        res.append((r,g,b))
    
    return res

def get_out_vect():
    for i in range(N):
        d1 = dist(i,(i+1)%N)
        xn1 = (xs[(i+1)%N] - xs[i])/d1
        yn1 = (ys[(i+1)%N] - ys[i])/d1
        d2 = dist(i,(i-1)%N)
        xn2 = (xs[(i-1)%N] - xs[i])/d2
        yn2 = (ys[(i-1)%N] - ys[i])/d2
        xav = (xn1+xn2)/2
        yav = (yn1+yn2)/2
        dav = sqrt(xav**2+yav**2)
        xav /= dav
        yav /= dav
        xn2 *= -1
        yn2 *= -1
        sinn = xn2*yav-xav*yn2
        sinn /= abs(sinn)
        xav *= -1*sinn
        yav *= -1*sinn
        pressure_vecs[i,0],pressure_vecs[i,1] = xav,yav

def check_free_T():
    global free_str
    non_free_T_num = 0
    for i in range(N):
        d = dist(i,(i+1)%N)
        xn = (xs[(i+1)%N]-xs[i])/d
        yn = (ys[(i+1)%N]-ys[i])/d
        v = xvs[i]*xn+yvs[i]*yn
        vn = xvs[(i+1)%N]*xn+yvs[(i+1)%N]*yn
        vr = v - vn
        if dist(i,(i+1)%N) > l0 and vr < 0:
            free_str[i] = [False,non_free_T_num]
            non_free_T_num += 1
        else:
            free_str[i] = [True,0]


def x0():
    return sum(xs)/N

def y0():
    return sum(ys)/N

def dist(i,j):
    return sqrt((xs[i]-xs[j])**2+(ys[i]-ys[j])**2) 