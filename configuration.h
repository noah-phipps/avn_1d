#pragma once
#ifndef CONFIGURATION_H
#define CONFIGURATION_H



//Parameters that need to be configured for the simulation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GENERAL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Simulation parameters
extern double sim_time;//Time for whole simulation //50 for N, 6 for NH //11.5 for AN
extern double start_record; //Start recording to file once time is greater than this //40 for N, 3.6 for NH//9 for AN

extern bool allow_main_simulation;

extern double stim_time;
extern int N_slow; //200
extern int N_fast; //325

extern double voltage;
extern double max_dep_voltage; //Maximum depolarizing voltage

extern int type;
//SET to TRUE to set I_bna to zero
extern bool i_bna_invest;
extern int solve_method;
extern int l;
extern bool SKF;
extern bool blockNa;
extern bool blockCa;
extern int answer;
extern int answer2;
extern int answer3;
extern double factor_block;// = 1;

extern double stim_current;


//Timestep details
extern double coarse_time_step;//Time step used initially
extern double fine_time_step ;//Time step switched to if required
extern double switch_to_fine;//Time to switch from coarse to fine at, set to longer than sim_time to avoid

extern bool am_open_fine;
extern bool n_open_fine;
extern bool an_open_fine;
extern bool nh_open_fine;

extern double total_time_taken;
extern double total_time_steps;
extern double time_per_step_estimate;
#endif