# -*- coding: utf-8 -*-
"""
Created on Wed Mar 24 14:10:43 2021

@author: nhphi
"""

# -*- coding: utf-8 -*-
"""
Created on Tue Oct 27 20:21:19 2020

@author: nhphi
"""

#Taking in output data from the AVN Initial Code and plotting it, for a specified cell
import numpy as np
import pyqtgraph as pg
import matplotlib.pyplot as plt

coupling = []
sodium = []
capacitance = []
cell = []
cell_type = []
filename = "fast_cell_details_original.txt"



with open(filename, 'r') as data:
    # Loop over each line
    a=0
    for line in data:
        
        p=line.split("\t")
        if(len(p)==4):
            cell_type.append(int(p[0]))
            if(int(p[0]) == 2):
                coupling.append(float(p[1]))
                sodium.append(float(p[2])*1E-12)
                capacitance.append(float(p[3]))
            else:
                coupling.append(float(p[1]))
                sodium.append(float(p[2]))
                capacitance.append(float(p[3]))
            cell.append(a)
            a+=1
        else:
            break #Exit the loop early, sloppy but effective
coupling = np.array(coupling)
sodium = np.array(sodium)
capacitance = np.array(capacitance)
cell=np.array(cell)

plt.figure(1)
plt.plot(cell,coupling*1E9)
plt.title("Coupling Conductance")


plt.figure(2)
plt.plot(cell,capacitance)
plt.title("Capacitance")


plt.figure(3)
plt.plot(cell,sodium*(1E9))
plt.title("Sodium Conductance")



            