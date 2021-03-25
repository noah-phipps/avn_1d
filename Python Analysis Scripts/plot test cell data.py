# -*- coding: utf-8 -*-
"""
Created on Tue Oct 27 20:21:19 2020

@author: nhphi
"""

#Taking in output data from the AVN Initial Code and plotting it, for a specified cell
import numpy as np
import pyqtgraph as pg
import matplotlib.pyplot as plt
list_of_lists = []
step = []
time=[]
am=[]
n=[]
an=[]
nh=[]
filename = "test_cells_original.txt"
timestep="5E-6"
simtime="2s"
titlestring = filename + ", " + timestep+" timestep, and " + simtime +" runtime."
   
with open(filename, 'r') as data:
    # loop over each line
    for line in data:
        # split the line into two strings using the ',' as a delimiter
        p = line.split("\t")
        if len(p)==6:
            time.append(float(p[0]))
            am.append(float(p[1]))
            n.append(float(p[2]))
            an.append(float(p[3]))
            nh.append(float(p[4]))

print("\nBeginning plotting...\n")

time=np.array(time)
am=np.array(am)
n=np.array(n)
an=np.array(an)
nh=np.array(nh)

#pg.plot(cell_data_to_plot)
#pg.plot(cell_data_to_plot)
fig=plt.figure(1)
plt.plot(time,am)
plt.title("am cell")

fig=plt.figure(2)
plt.plot(time,n)
plt.title("n cell")

fig=plt.figure(3)
plt.plot(time,an)
plt.title("an cell")

fig=plt.figure(4)
plt.plot(time,nh)
plt.title("nh cell")



            