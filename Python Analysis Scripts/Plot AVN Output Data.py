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
filename = "fast_cells_original.txt"
timestep="5E-8"
simtime="0.2s"
titlestring = filename + ", " + timestep+" timestep, and " + simtime +" runtime."

with open(filename, 'r') as data:
    # Loop over each line
    a=0
    for line in data:
        
        a+=1 
        if(a==1):
            p=line.split("\t")
            for i in range(len(p)-2):
                new_list =[]
                list_of_lists.append(new_list)
        else:
            break #Exit the loop early, sloppy but effective
                
b=0           
print("\n")
print(len(list_of_lists))
print("values detected in first line.")
print("\n")     
with open(filename, 'r') as data:
    # loop over each line
    for line in data:
        step.append(int(b))
        b+=1
        # split the line into two strings using the ',' as a delimiter
        p = line.split("\t")
        time.append(float(p[0]))
        for i in range(len(p)-2):#account for time and extra \t
            
            try:
                list_of_lists[i].append(float(p[i+1]))#extra \t is at the end, so only need +1
            except:
                list_of_lists[i].append(0.0)

print("\n")
print(b)
print(" lines imported.\n")            

steps = np.array(step)
cell_data_to_plot = np.array(list_of_lists[0])
print("\nBeginning plotting...\n")
#pg.plot(cell_data_to_plot)
#pg.plot(cell_data_to_plot)
fig=plt.figure()
ax1=fig.add_subplot(111)
#plotWidget = pg.plot(title="All cell data")
for i in range(len(list_of_lists)-1):
#    plotWidget.plot(list_of_lists[i], pen=(i,len(list_of_lists)-1))
    #pg.plot(list_of_lists[i])
    if(len(time)!= len(list_of_lists[i])):
            newtime=time.copy()
            newtime.pop(len(newtime)-1)
            ax1.plot(newtime,np.array(list_of_lists[i]))
    else:
            ax1.plot(time,np.array(list_of_lists[i]))
print("\Completed plotting!\n")
ax1.set_title(titlestring)
ax1.set_xlabel("Time (s)")
ax1.set_ylabel("Voltage")
#plt.show()




            