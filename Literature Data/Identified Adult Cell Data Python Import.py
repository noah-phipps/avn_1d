# -*- coding: utf-8 -*-
"""
Created on Thu Nov 19 10:19:40 2020

@author: nhphi
"""

#Reading in literature data for adult cells
import numpy as np
import pyqtgraph as pg
import matplotlib.pyplot as plt
from cycler import cycler

experiment = []
cell_type = []
resting = []
resting_err =[]
amplitude =[]
amplitude_err=[]
dv_dt_max=[]
dv_dt_max_err=[]
MDP =[]
MDP_err=[]
overshoot=[]
overshoot_err=[]
APD90=[]
APD90_err=[]
APD50=[]
APD50_err=[]
cycle_length=[]
cycle_length_err=[]
ARP=[]
ARP_err=[]
RRP=[]
RRP_err=[]
DDR=[]
DDR_err=[]

#using 99999 to denote invalid values
filename = "Identified Adult Cell Data.csv"

i = 0

with open(filename, 'r') as data:
    # Loop over each line
    for line in data:
        p=line.split(",")
        experiment.append(p[0])
        cell_type.append(p[1])
        try:
            resting.append(float(p[2]))
            resting_err.append(float(p[3]))
        except:
            resting.append(99999)
            resting_err.append(99999)
        try:
            amplitude.append(float(p[4]))
            amplitude_err.append(float(p[5]))
        except:
            amplitude.append(99999)
            amplitude_err.append(99999)
        try:
            dv_dt_max.append(float(p[6]))
            dv_dt_max_err.append(float(p[7]))
        except:
            dv_dt_max.append(99999)
            dv_dt_max_err.append(99999)
        try:
            MDP.append(float(p[8]))
            MDP_err.append(float(p[9]))
        except:
            MDP.append(99999)
            MDP_err.append(99999)
        try:
            overshoot.append(float(p[10]))
            overshoot_err.append(float(p[11]))
        except:
            overshoot.append(99999)
            overshoot_err.append(99999)
        try:
            APD90.append(float(p[12]))
            APD90_err.append(float(p[13]))
        except:
            APD90.append(99999)
            APD90_err.append(99999)
        try:
            APD50.append(float(p[14]))
            APD50_err.append(float(p[15]))
        except:
            APD50.append(99999)
            APD50_err.append(99999)
        try:
            cycle_length.append(float(p[16]))
            cycle_length_err.append(float(p[17]))
        except:
            cycle_length.append(99999)
            cycle_length_err.append(99999)
        try:
            ARP.append(float(p[18]))
            ARP_err.append(float(p[19]))
        except:
            ARP.append(99999)
            ARP_err.append(99999)
        try:
            RRP.append(float(p[20]))
            RRP_err.append(float(p[21]))
        except:
            RRP.append(99999)
            RRP_err.append(99999)
        try:
            DDR.append(float(p[22]))
            DDR_err.append(float(p[23]))
        except:
            DDR.append(99999)
            DDR_err.append(99999)
    
#######################################
#Plotting resting potential
tick_interval=1
plt.figure(1)
array=resting
array_err=resting_err
plotted="Resting Potential"
units="mV"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(2)
array=resting
array_err=resting_err
plotted="Resting Potential"
units="mV"

k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(3)
array=resting
array_err=resting_err
plotted="Resting Potential"
units="mV"

k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################
 #Plotting amplitude 
tick_interval=5
plt.figure(4)
array=amplitude
array_err=amplitude_err
plotted="Amplitude"
units="mV"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(5)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(6)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################
 #Plotting dv_dt_max 
tick_interval=5
plt.figure(7)
array=dv_dt_max
array_err=dv_dt_max_err
plotted="dv/dt_max"
units="V/s"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(8)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(9)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################  
 #Plotting mdp 
tick_interval=5
plt.figure(10)
array=MDP
array_err=MDP_err
plotted="MDP"
units="mV"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(11)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(12)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################        
 ##############################################################################################################################  
 #Plotting overshoot 
tick_interval=5
plt.figure(13)
array=overshoot
array_err=overshoot_err
plotted="Overshoot"
units="mV"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(14)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(15)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################                          
  ##############################################################################################################################  
 #Plotting apd90 
tick_interval=5
plt.figure(16)
array=APD90
array_err=APD90_err
plotted="APD90"
units="ms"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(17)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(18)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################   
  ##############################################################################################################################  
 #Plotting apd50 
tick_interval=5
plt.figure(19)
array=APD50
array_err=APD50_err
plotted="APD50"
units="ms"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(20)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(21)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################   
  ##############################################################################################################################  
 #Plotting mdp 
tick_interval=100
plt.figure(22)
array=cycle_length
array_err=cycle_length_err
plotted="Cycle Length"
units="ms"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    

 #################################
 ##############################################################################################################################  
 ##############################################################################################################################  
 #Plotting mdp 
tick_interval=100
plt.figure(23)
array=ARP
array_err=ARP_err
plotted="ARP"
units="ms"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
 ##############################################################################################################################  
 #Plotting mdp 
tick_interval=100
plt.figure(24)
array=RRP
array_err=RRP_err
plotted="RRP"
units="ms"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
 ##############################################################################################################################  
 #Plotting mdp 
tick_interval=5
plt.figure(25)
array=DDR
array_err=DDR_err
plotted="DDR"
units="V/s"

k=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for AN cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)

values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units))    
#Plotting resting potential 
plt.figure(26)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for N cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k) 
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
plt.figure(27)


k=1
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            values.append(array[i])
            errors.append(array_err[i])
            weight=1/(array_err[i]*array_err[i])
            weight_sum+=weight
            weight_times_value_sum+=(weight*array[i])
            plt.scatter(k,array[i],label=experiment[i])
            plt.errorbar(k,array[i],yerr=array_err[i],markersize=8,elinewidth=2,capsize=10,markeredgewidth=2)
            k+=1
plt.title(plotted + " for NH cells")
plt.ylabel(plotted+" ("+units+")")
plt.legend()
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
x=np.arange(-1,k+1,0.01)
upper_lim=(mean+mean_err)*(x/x)
lower_lim=(mean-mean_err)*(x/x)
plt.plot([-1,k+1],[mean,mean],color='black')
plt.fill_between(x,lower_lim,upper_lim,color='green',alpha=0.5)
plt.xlim(0,k)
values=np.array(values)
errors=np.array(errors)
max_plots=errors+values
min_plots=values-errors
plt.yticks(np.arange((min_plots.min()).round() -2, (max_plots.max().round()) + 2, tick_interval))
plt.grid(axis='y',which='major')
plt.xticks(np.arange(0,k,1))
plt.tick_params(labelbottom=False)
plt.xlabel("Average is ("+ "{:.2f}".format(mean)+ " +/- "+ "{:.2f}".format(mean_err) + ") "+str(units)) 
 #################################
 ##############################################################################################################################   