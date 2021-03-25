# -*- coding: utf-8 -*-
"""
Created on Fri Mar 19 18:19:48 2021

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


stimcurrent=[]
time=[]

timestep= "5E-8"
celltype = "AM"
filename = "am_test_stim_current_original.txt"
titlestring = filename + " for " + celltype + " cell, " + timestep+" timestep."

with open(filename, 'r') as data:
    # loop over each line
    for line in data:
        # split the line into two strings using the ',' as a delimiter
        p = line.split("\t")
        if(len(p)==2):
            time.append(float(p[0]))
            stimcurrent.append(float(p[1]))
          

plt.plot(np.array(time),np.array(stimcurrent))




            