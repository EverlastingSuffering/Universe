import numpy as np
from math import *
from constants import *
import random as rnd

free_str = [[False,0] for i in range(N)] 
pressure_vecs = np.zeros((N,2),dtype="float64")
Ts = np.zeros((N,))
xs = np.array([0.5*box_w+R*cos(i) for i in np.arange(0,2*pi,2*pi/N)],dtype="float64")
xvs = np.array([rnd.random()*5 for _ in range(N)],dtype="float64")
ys = np.array([0.5*box_h+R*sin(i)-7 for i in np.arange(0,2*pi,2*pi/N)],dtype="float64")
yvs = np.array([rnd.random()*5 for _ in range(N)],dtype="float64")

xws = np.array()