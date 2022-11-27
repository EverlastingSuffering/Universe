from math import *
import numpy as np
import random as rnd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from constants import *
from calcs import *
from misc import *
from points import *
from timef import *

fig,ax = plt.subplots()
lines = []
for i in range(N):
    line, = ax.plot([xs[i],xs[(i+1)%N]],[ys[i],ys[(i+1)%N]],'b-',linewidth=2)
    lines.append(line)
ax.set_ylim([-0.1*box_h,box_h*1.1])
ax.set_xlim([-0.1*box_w,box_w*1.1])
ax.set_aspect('equal', adjustable='box')
stats = ax.text(box_w*0.01,box_h*0.99,"",fontsize=10)
start_time_clock = datetime.now()
curr_time = 0

def print_eta(dtt):
    curr_time_clock = datetime.now()
    laps = curr_time_clock-start_time_clock
    eta = (T-curr_time)/curr_time*laps.total_seconds()
    res = "\rTime processed: " + str(round(curr_time,4)) + "; ETA: " + str(round(eta,1)) + "; Current dt: " + str(round(dtt,6)) + " s"
    res += " "*10
    print(res,end=' ')

def main(ii):
    global curr_time,dt
    check_free_T()
    get_out_vect()
    find_T()
    #strings()
    avy = 0
    avx = 0
    avfx = 0
    avfy = 0
    curr_xvs = np.zeros((N,))
    curr_yvs = np.zeros((N,))
    curr_vs = np.zeros((N,))
    curr_xas = np.zeros((N,))
    curr_yas = np.zeros((N,))
    curr_as = np.zeros((N,))
    for i in range(N):
        curr_xvs[i] = x1_eq(i)
        curr_yvs[i] = y1_eq(i)
        curr_vs[i] = sqrt(curr_xvs[i]**2+curr_yvs[i]**2)
        curr_xas[i] = xv1_eq(i)
        curr_yas[i] = yv1_eq(i)
        curr_as[i] = sqrt(curr_xas[i]**2+curr_yas[i]**2)
    max_v = max(curr_vs,key=lambda x: abs(x))
    stretched_vs = [abs(curr_vs[i]) for i in range(N) if not free_str[i] or not free_str[(i-1)%N]]
    if stretched_vs:
        min_v = min(stretched_vs)
    else:
        min_v = max_v
    max_a = max(curr_as,key=lambda x: abs(x))
    dtt = max(min(dt,min(PERCICION*l0/abs(max_v),PERCICION*abs(min_v)/max(abs(max_a),eps))),min_dt)
    curr_time += dtt
    for i in range(N):
        xs[i] += dtt*curr_xvs[i]
        ys[i] += dtt*curr_yvs[i]
        xvs[i] = xvs[i] + dtt*curr_xas[i]
        yvs[i] = yvs[i] + dtt*curr_yas[i]
        avx += xvs[i]/N
        avy += yvs[i]/N
        avfx += curr_xas[i]*m/N
        avfy += curr_yas[i]*m/N
    colors = get_tension_colors()
    for i,line in enumerate(lines):
        line.set_data([xs[i],xs[(i+1)%N]],[ys[i],ys[(i+1)%N]])
        line.set_color(colors[i])
    av = sqrt(avx**2+avy**2)
    af = sqrt(avfx**2+avfy**2)
    stats_str = "Aver. Vx: " + str(round(avx,3)) + '\n' + "Aver. Vy: " + str(round(avy,3)) + '\n' + "Aver. V: " + str(round(av,3)) + '\n'
    stats_str += "Aver. Fx: " + str(round(avfx,3)) + '\n' + "Aver. Fy: " + str(round(avfy,3)) + '\n' + "Aver. V: " + str(round(af,3)) + '\n'
    stats_str += "Time: " + str(round(curr_time,4))
    stats.set_text(stats_str)
    print_eta(dtt)

    return dtt


def animate(ii):
    global curr_time
    super_speed_boost = False
    dtt = dt/SPEED_BOOST
    curr_time = ii
    while curr_time < ii+dt:
        curr_time += dtt
        dtt = main(curr_time)
    return lines

ts = [i for i in np.arange(0,T,dt)]
plt.show()
ani = animation.FuncAnimation(fig,animate,ts,interval=5000*dt)
ani.save("movie1.mp4")