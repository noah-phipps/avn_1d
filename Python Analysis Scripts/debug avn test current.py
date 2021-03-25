# -*- coding: utf-8 -*-
"""
Created on Thu Mar 11 20:34:46 2021

@author: nhphi
"""

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

cell = "nh"

cell_type=[]
time=[]
#names are wrong but labels are correct
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
filename_suffix = "_test_currents_original.txt"
filename=cell+filename_suffix
titlestring = filename + " for " + cell + " cell, " + timestep+" timestep."

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
avn_labels=[]
avn_labels.append("I Na")
avn_labels.append("I l")
avn_labels.append("I kr")
avn_labels.append("I f")
avn_labels.append("I st")
avn_labels.append("I tp")
avn_labels.append("I p")
avn_labels.append("I naca")
avn_labels.append("I b")
avn_labels.append("I k1")
avn_labels.append("I sus")

#names are wrong but labels are correct
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
for i in range(len(avn_labels)):
    #plotWidget.plot(list_of_lists[i], pen=(i,len(list_of_lists)))
    #pg.plot(list_of_lists[i])
        ax1.plot(np.array(time),np.array(list_of_lists[i]),label=avn_labels[i])
print("\Completed plotting!\n")
ax1.set_title(titlestring)
ax1.set_xlabel('Time (s)')
ax1.set_ylabel('Current Value')
ax1.legend()
plt.show




            