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
import sys

keep_figs_open=True
try:
    plt.close("all")
except:
    print("No open figures to close...\n")

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

NDataOut=open("N Cell Averages.txt","w")
NHDataOut=open("NH Cell Averages.txt","w")
ANDataOut=open("AN Cell Averages.txt","w")

NRawDataOut=open("Raw N Cell Averages.txt","w")
ANRawDataOut=open("Raw AN Cell Averages.txt","w")
NHRawDataOut=open("Raw NH Cell Averages.txt","w")

#using 99999 to denote invalid values
filename = "Identified Adult Cell Data.csv"

i = 0

with open(filename,'r') as data:
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
data.close()
#######################################
            #Create an experiment color map
unique_experiments=0
correct_length_color_list=[]
for i in range(len(experiment)):
    a=0
    for k in range(0,i):
        if(experiment[k]==experiment[i]):
            a+=1
    if(a==0):
        unique_experiments+=1
        
color_list = plt.cm.tab20(np.linspace(0,1,unique_experiments))
j=-1
for i in range(len(experiment)):
    a=0
    for k in range(0,i):
        if(experiment[k]==experiment[i]):
            a+=1
    if(a==0):
        j+=1
        correct_length_color_list.append(color_list[j])
    else:
        correct_length_color_list.append(color_list[j])

###################################################################################################################
experiment[1]='Action Potential Changes under Varied [Na+ ]0 and [Ca2+]0 Indicating the Existence of Two Inward Currents in \nCells of the Rabbit Atrioventricular Node'
experiment[2]='Action Potential Changes under Varied [Na+ ]0 and [Ca2+]0 Indicating the Existence of Two Inward Currents in \nCells of the Rabbit Atrioventricular Node'
experiment[3]='Action Potential Changes under Varied [Na+ ]0 and [Ca2+]0 Indicating the Existence of Two Inward Currents in \nCells of the Rabbit Atrioventricular Node'


#Plotting resting potential
tick_interval=1
fig = plt.figure(1)
array=resting
array_err=resting_err
plotted="Resting Potential"
units="mV"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
values=np.array(values)
errors=np.array(errors)
ANk_high=k


#k+=5
#values=[]
#errors=[]
#weight_sum=0
#weight_times_value_sum=0
#Nk_low=k
#for i in range(len(array)):
#    if(cell_type[i]=="N"):
#        if(array[i]!=99999):
#            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
#                values.append(array[i])
#                errors.append(array_err[i])
#                weight=1/(array_err[i]*array_err[i])
#                weight_sum+=weight
#                weight_times_value_sum+=(weight*array[i])
#                any_used= False
#                for j in range(len(labels_used)):
#                    if(experiment[i]==labels_used[j]):
#                        any_used=True
#                if(any_used==True):
#                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
#                else:
#                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
#                    labels_used.append(experiment[i])
#                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
#                k+=1
#for i in range(len(array)):
#    if(cell_type[i]=="N"):
#        if(array[i]!=99999):
#            if(experiment[i]=="Inada Simulation"):
#                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
#                k+=1
#            if(experiment[i]=="Previous Project Simulation"):
#                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
#                k+=1
#            if(experiment[i]=="Simulation"):
#                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
#                k+=1
#mean=weight_times_value_sum/weight_sum
#mean_err=1/(weight_sum**0.5)
#NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
#NDataOut.write(units + "\n")
#NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
#NRawDataOut.write("\n")
#plt.scatter(k,mean,color='black',label='Weighted Average')
#plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
#Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(2)
array=amplitude
array_err=amplitude_err
plotted="Amplitude"
units="mV"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
values=np.array(values)
errors=np.array(errors)
ANk_high=k


k+=5
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(Nk_low+Nk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","N Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.05),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
 ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(3)
array=dv_dt_max
array_err=dv_dt_max_err
plotted="dv dt Max Value"
units="V/s"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
values=np.array(values)
errors=np.array(errors)
ANk_high=k


k+=5
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(Nk_low+Nk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","N Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.3,
                 box.width, box.height*0.8])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.07),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(8,6)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
 ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(4)
array=MDP
array_err=MDP_err
plotted="MDP"
units="mV"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
values=np.array(values)
errors=np.array(errors)
ANk_high=k


k+=5
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(Nk_low+Nk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","N Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.07),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(8,6)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
 ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(5)
array=overshoot
array_err=overshoot_err
plotted="Overshoot"
units="mV"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
values=np.array(values)
errors=np.array(errors)
ANk_high=k


k+=5
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(Nk_low+Nk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","N Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.07),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(8,6)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
 ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(6)
array=APD90
array_err=APD90_err
plotted="APD90"
units="ms"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
values=np.array(values)
errors=np.array(errors)
ANk_high=k


k+=5
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(Nk_low+Nk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","N Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.07),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(8,6)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
 ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(7)
array=APD50
array_err=APD50_err
plotted="APD50"
units="ms"

k=1
ANk_low=1
weight_sum=0
weight_times_value_sum=0
values=[]
errors=[]
labels_used=[]
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i], color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="AN"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
ANDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
ANDataOut.write(units + "\n")
ANRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
ANRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
values=np.array(values)
errors=np.array(errors)
ANk_high=k


k+=5
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k


k+=5
NHk_low=k
values=[]
errors=[]
weight_sum=0
weight_times_value_sum=0
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="NH"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i], color='red',marker='X',s=50)
                k+=1
NHk_high=k
plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NHDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NHDataOut.write(units + "\n")
NHRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NHRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(ANk_low+ANk_high)/2,(Nk_low+Nk_high)/2,(NHk_low+NHk_high)/2],labels=["AN Cells","N Cells","NH Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])
    
# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
 ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(8)
array=cycle_length
array_err=cycle_length_err
plotted="Cycle Length"
units="ms"

k=1

values=[]
errors=[]
labels_used=[]

weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k

plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(Nk_low+Nk_high)/2],labels=["N Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
  ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(9)
array=ARP
array_err=ARP_err
plotted="ARP"
units="ms"

k=1

values=[]
errors=[]
labels_used=[]

weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k

plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(Nk_low+Nk_high)/2],labels=["N Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
  ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(10)
array=RRP
array_err=RRP_err
plotted="RRP "
units="ms"

k=1

values=[]
errors=[]
labels_used=[]

weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k

plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(Nk_low+Nk_high)/2],labels=["N Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
  ###################################################################################################################
#Plotting resting potential
tick_interval=1
fig = plt.figure(11)
array=DDR
array_err=DDR_err
plotted="DDR"
units="V/s"

k=1

values=[]
errors=[]
labels_used=[]

weight_sum=0
weight_times_value_sum=0
Nk_low=k
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]!="Simulation" and experiment[i]!="Inada Simulation" and experiment[i]!="Previous Project Simulation"):
                values.append(array[i])
                errors.append(array_err[i])
                weight=1/(array_err[i]*array_err[i])
                weight_sum+=weight
                weight_times_value_sum+=(weight*array[i])
                any_used= False
                for j in range(len(labels_used)):
                    if(experiment[i]==labels_used[j]):
                        any_used=True
                if(any_used==True):
                   plt.scatter(k,array[i],label="_nolegend_",color=correct_length_color_list[i])
                else:
                    plt.scatter(k,array[i],label=experiment[i],color=correct_length_color_list[i])
                    labels_used.append(experiment[i])
                plt.errorbar(k,array[i],yerr=array_err[i],color=correct_length_color_list[i],markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
                k+=1
for i in range(len(array)):
    if(cell_type[i]=="N"):
        if(array[i]!=99999):
            if(experiment[i]=="Inada Simulation"):
                plt.scatter(k,array[i],color='red',marker='D',label="Inada Simulation",s=50)
                k+=1
            if(experiment[i]=="Previous Project Simulation"):
                plt.scatter(k,array[i],color='red',marker='s',label="Previous Project Simulation",s=50)
                k+=1
            if(experiment[i]=="Simulation"):
                plt.scatter(k,array[i],label="Simulation Data", color='red',marker='X',s=50)
                k+=1
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
NDataOut.write(plotted + " average: (%.2f +/- %.2f) "%(mean,mean_err))
NDataOut.write(units + "\n")
NRawDataOut.write("%.2f, %.2f"%(mean,mean_err))
NRawDataOut.write("\n")
plt.scatter(k,mean,color='black',label='Weighted Average')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
Nk_high=k

plt.ylabel(plotted+" ("+units+")")
mean=weight_times_value_sum/weight_sum
mean_err=1/(weight_sum**0.5)
plt.scatter(k,mean,color='black')
plt.errorbar(k,mean,yerr=mean_err,color='black',markersize=8,elinewidth=2,capsize=5,markeredgewidth=2)
plt.grid(which='major',axis='y')
plt.title(plotted + " Data")
plt.xticks(ticks=[(Nk_low+Nk_high)/2],labels=["N Cells"])

ax=fig.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * .9])

# Put a legend below current axis
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=1,prop={'size': 6})

figure=plt.gcf()
figure.set_size_inches(6,5)
plt.savefig(plotted,dpi=100)
####################
 ##############################################################################################################################
NDataOut.close()
ANDataOut.close()
NHDataOut.close()
NRawDataOut.close()
ANRawDataOut.close()
NHRawDataOut.close()
if(keep_figs_open!=True):
    plt.close("all")
    print("All figures saved and closed...")
else:
    print("All figures saved and kept open...")