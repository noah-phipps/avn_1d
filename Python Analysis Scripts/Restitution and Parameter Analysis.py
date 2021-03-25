# -*- coding: utf-8 -*-
"""
Created on Mon Dec 14 09:05:18 2020

@author: nhphi
"""

#Restitution and Parameter Analysis
#Requires a simulation with restitution value 0.4s to be saved
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  3 15:29:52 2020

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
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
import math
plt.close('all')
plot_voltage = False
celltype = "AM"
user_start_time=0.0
user_celltype=1

def find_nearest(array,value):
    idx = np.searchsorted(array, value, side="left")
    if idx > 0 and (idx == len(array) or math.fabs(value - array[idx-1]) < math.fabs(value - array[idx])):
        return idx-1
    else:
        return idx

def find_downstroke_value_index(array,low_index,high_index,value):
    best_diff=100
    best_index=0
    for i in range(low_index,high_index):
        new_diff=abs(array[i]-value)
        if(new_diff<best_diff):
            best_diff=new_diff
            best_index=i
    return best_index

def analyse_voltage_data(start_time,data,celltype):
    plt.figure(1)
    timestep = "5E-8"
    celltype = "AM"
    stimulation_one = None
    stimulation_two = None
    periodic_stimulation = True
    stim_one_time = "0.4"
    stim_two_time = "1.6"
    #data is a list of two lists; data[0] is time, data[1] is voltage
    #Data we want to return
    overshoot = 0
    MDP = 0
    amplitude=0
    dv_dt_max = 0
    APD90 = 0
    APD50 = 0
    cycle_length = 0
    frequency = 0
    DDR = 0
    ARP = 0
    RRP = 0
    resting_potential = 0
    
    

    dvdt_array = np.array(data[2])
    time_array=np.array(data[0])
    voltage_array=np.array(data[1])
    low_index_limit = find_nearest(time_array,start_time)
    print("Limiting low time detected at index {} of {}.".format(low_index_limit,len(time_array)))
    if(low_index_limit>len(time_array)):
        print("ERROR! Index found is greater than array length.")
    for i in range(0,low_index_limit):
        time_array=np.delete(time_array,[0])
        voltage_array=np.delete(voltage_array,[0])
        dvdt_array=np.delete(dvdt_array,[0])
        i+=1
    print("Finished deleting unneccessary data...")
    #Now have the arrays limited for the low limit
    #Now want to find maxima in the voltage data:
    maxima_indexes, _ =find_peaks(voltage_array,height=0.02)
    timestep=5E-8
    horizontal_time=0.0001
    minina_indexes, _ =find_peaks((voltage_array*-1),height=0.035,distance=horizontal_time/timestep)
    dvdt_peak_indexes, _ = find_peaks(dvdt_array,height=1,distance=horizontal_time/timestep)
    #Now want to do the analysis
    #Find overshoot average:
    number_peaks=len(maxima_indexes)
    for i in range(number_peaks):
        overshoot+=voltage_array[maxima_indexes[i]]
    try:
        overshoot=overshoot/number_peaks
    except:
        print("Overshoot below 0mV error, plotting graph and exiting...")
        plt.plot(timelist,datalist)
        return
    #Now MDP:
    number_troughs=len(minina_indexes)
    print((maxima_indexes))
    print((minina_indexes))
    
    for i in range(len(maxima_indexes)):
        plt.scatter(time_array[maxima_indexes[i]],voltage_array[maxima_indexes[i]]*1000,color='red')
        
    for i in range(len(minina_indexes)):
        plt.scatter(time_array[minina_indexes[i]],voltage_array[minina_indexes[i]]*1000,color='red')
        
    for i in range(len(dvdt_peak_indexes)):
        plt.scatter(time_array[dvdt_peak_indexes[i]],voltage_array[dvdt_peak_indexes[i]]*1000,color='green')
        
    for i in range(number_troughs):
        MDP+=voltage_array[minina_indexes[i]]
    try:
        
        MDP = MDP/number_troughs
    except:
        print("MDP above 0mV error, plotting graph and exiting...")
        plt.plot(timelist,datalist)
        return
    
    #Now cycle length:
    a=0
    for i in range(1,number_peaks):
        cycle_length+=(time_array[maxima_indexes[i]]-time_array[maxima_indexes[i-1]])
        a+=1
    cycle_length=cycle_length/a
    frequency=1/cycle_length
    
    #Now dv_dt:
    dv_dt_max = np.max(dvdt_array)#Difficult to take an average, have to find max for each upstroke
    
    #Now APD90 and APD50 and amplitude:
    b=0
    for i in range(number_troughs-1):
        #if(minina_indexes[i+1]<maxima_indexes[len(maxima_indexes)-1]):

            peak_time_index=0
            dvdt_peak_time_index=0
            try:
                low_val=minina_indexes[i]
                high_val=minina_indexes[i+1]
                for j in range(len(maxima_indexes)):
                    if(maxima_indexes[j]>low_val and maxima_indexes[j]<high_val):
                        peak_time_index=maxima_indexes[j]
                    if(dvdt_peak_indexes[j]>low_val and dvdt_peak_indexes[j]<high_val):
                        dvdt_peak_time_index=dvdt_peak_indexes[j]
            except:
                print("Error! could not find peak in APD90 analysis.")
            start_time=time_array[dvdt_peak_time_index]
            end_time=time_array[minina_indexes[i+1]]
            peak_time=time_array[peak_time_index]
            start_voltage=voltage_array[minina_indexes[i]]
            end_voltage=voltage_array[minina_indexes[i+1]]
            peak_voltage=voltage_array[peak_time_index]
            this_amplitude = peak_voltage-end_voltage
            voltage_90=peak_voltage-(this_amplitude*0.9)
            voltage_50=peak_voltage-(this_amplitude*0.5)
            pass_value_1=peak_time_index
            pass_value_2=minina_indexes[i+1]
            index_90 = find_downstroke_value_index(voltage_array,pass_value_1,pass_value_2,voltage_90)
            index_50 = find_downstroke_value_index(voltage_array,pass_value_1,pass_value_2,voltage_50)
            plt.scatter(time_array[dvdt_peak_time_index],voltage_array[dvdt_peak_time_index]*1000,color='black',marker="x")
            plt.scatter(time_array[index_90],voltage_array[index_90]*1000,color='black',marker="x")
            APD90+=time_array[index_90]-start_time
            APD50+=time_array[index_50]-start_time
            amplitude+=this_amplitude
            b+=1#count another measurement
    try:
        APD90=APD90/b
        APD50=APD50/b
        amplitude=amplitude/b
    except:
        print("Divide by zero error with APD and amplitude, b=0; peak at end.")
    
    resting_potential=voltage_array[len(voltage_array)-1]
    plt.scatter(time_array[len(voltage_array)-1],voltage_array[len(voltage_array)-1]*1000,color='orange')

    print("Printing parameters...\n\n\n")
    print("Overshoot is {:.2f} mV (Actual maxima is {:.2f} mV)\n".format(overshoot*1000,np.max(voltage_array)*1000))
    print("MDP is {:.2f} mV (Actual minima is {:.2f} mV)\n".format(MDP*1000,np.min(voltage_array)*1000))
    print("Amplitude is {:.2f} mV \n".format(overshoot*1000-MDP*1000))
    print("dv_dt_max is {:.2f} V/s (Actual maxima is {:.2f} V/s)\n".format(dv_dt_max,np.max(dvdt_array)))
    print("APD90 is {:.2f} ms\n".format(APD90*1000))
    print("APD590 is {:.2f} ms\n".format(APD50*1000))
    print("Cycle length is {:.2f} ms\n".format(cycle_length*1000))
    print("Frequency is {:.2f} Hz\n".format(frequency))
    print("DDR is {:.2f} \n".format(DDR))
    print("ARP is {:.2f} \n".format(ARP))
    print("RRP is {:.2f} \n".format(RRP))
    print("Resting_potential is {:.2f} mV\n".format(resting_potential*1000))
        
    #print("First peak detected at " + time_array[maxima_indexes[0]]*1000 + "ms, with the first minima at " + time_array[minina_indexes[0]]*1000 + "ms.")
    plt.plot(time_array,voltage_array*1000)
    

    parameter_data ="\nSimulation performed using reformulated cell parameters."
    title_string = celltype + " Single Cell Simulation, with " + str(timestep) + " time step.\n"
    if(stimulation_one==None and stimulation_two==None and periodic_stimulation == None):
        title_string+=" No stimulations."
    if(stimulation_one==True and stimulation_two==None):
        title_string+=" Single stimulation at " + stim_one_time + " s."
    if(stimulation_two==True):
        title_string+=" Stimulations at " + stim_one_time + " s and " + stim_two_time + "s."
    if(periodic_stimulation == True):
        title_string+=" Periodic stimulations every 0.4s starting at 0.4s."
    title_string+=parameter_data
    plt.title(title_string)
    plt.xlabel("Time (s)")
    plt.ylabel("Vm (mV)")
    #plt.ylim(-.08,.04)
    plt.xlim(np.min(timelist), np.max(timelist))
    plt.grid()
    #plt.xticks(np.arange(np.min(timelist),np.max(timelist),0.1))
    plt.show()
filename = "test_cells_original.txt"
datalist = []
timelist = []
dvdtlist = []
all_data = []


i = 0

with open(filename, 'r') as data:
    # Loop over each line
    for line in data:
        i+=1
        p=line.split("\t")
        try:
            datalist.append(float(p[1]))
            timelist.append(float(p[0]))
            dvdtlist.append(float(p[2]))
        except:
            break
print("{} lines imported.".format(i))
all_data.append(timelist)
all_data.append(datalist)
all_data.append(dvdtlist)
timelist=np.array(timelist)
datalist=np.array(datalist)
dvdtlist=np.array(dvdtlist)

analyse_voltage_data(user_start_time,all_data,user_celltype)




