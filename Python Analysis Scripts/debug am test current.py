# -*- coding: utf-8 -*-
"""
Created on Thu Mar 11 20:15:26 2021

@author: nhphi
"""

# -*- coding: utf-8 -*-
"""
Created on Sun Nov  1 13:54:57 2020

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
from cycler import cycler


cell_type=[]
time=[]
na=[]
k=[]
k1=[]
to=[]
naca=[]
p_=[]
b=[]
cap=[]
cal=[]
cat=[]
sus=[]
list_of_lists=[]
timestep= "5E-8"
celltype = "AM"
filename = "am_test_currents_original.txt"
titlestring = filename + " for " + celltype + " cell, " + timestep+" timestep."

with open(filename, 'r') as data:
    # loop over each line
    for line in data:
        # split the line into two strings using the ',' as a delimiter
        p = line.split("\t")
        if(len(p)==13):
            cell_type.append(float(p[0]))
            time.append(float(p[1]))
            na.append(float(p[2]))
            k.append(float(p[3]))
            k1.append(float(p[4]))
            to.append(float(p[5]))
            naca.append(float(p[6]))
            p_.append(float(p[7]))
            b.append(float(p[8]))
            cap.append(float(p[9]))
            cal.append(float(p[10]))
            cat.append(float(p[11]))
            sus.append(float(p[12]))
          

#Celltype of 0 is am_cell
am_labels=[]
am_labels.append("INa")
am_labels.append("IK")
am_labels.append("Ik1")
am_labels.append("Ito")
am_labels.append("INaCa")
am_labels.append("Ip")
am_labels.append("Ib")
am_labels.append("ICap")
am_labels.append("ICal")
am_labels.append("ICat")
am_labels.append("Isus")

list_of_lists.append(na)
list_of_lists.append(k)
list_of_lists.append(k1)
list_of_lists.append(to)
list_of_lists.append(naca)
list_of_lists.append(p_)
list_of_lists.append(b)
list_of_lists.append(cap)
list_of_lists.append(cal)
list_of_lists.append(cat)
list_of_lists.append(sus)






print("\nBeginning plotting...\n")
#pg.plot(cell_data_to_plot)
#pg.plot(cell_data_to_plot)
fig=plt.figure()
ax1=fig.add_subplot(111)

ax1.set_prop_cycle(cycler('color', ['b', 'g', 'r', 'c', 'm', 'y', 'k','b', 'g', 'r', 'c', 'm', 'y', 'k', 'b', 'g', 'r', 'c', 'm', 'y', 'k']) + 
                   cycler('linestyle',['-', '-', '-', '-', '-', '-', '-', '--', '--', '--', '--', '--', '--', '--', ':', ':', ':', ':', ':', ':', ':'])
                   )
#plotWidget = pg.plot(title="All cell data")
for i in range(len(am_labels)):
    #plotWidget.plot(list_of_lists[i], pen=(i,len(list_of_lists)))
    #pg.plot(list_of_lists[i])
        ax1.plot(np.array(time),np.array(list_of_lists[i]),label=am_labels[i])
print("\Completed plotting!\n")
ax1.set_title(titlestring)
ax1.set_xlabel('Time (s)')
ax1.set_ylabel('Current Value')
ax1.legend()
plt.show




            