/*--------------------------------------------------------------------
-------- -
AVN Model Configuration File
21 / 03 / 2021	Created by Noah PHIPPS 
--------------------------------------------------------------------
------ */

#pragma once
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include<string>

//Parameters that need to be configured for the simulation
//All declared as externals here, configure in the .cpp file

extern bool run_in_remote_configuration;
extern bool allow_test_cells;
extern double sim_time;//Time for whole simulation //50 for N, 6 for NH //11.5 for AN
extern double start_record; //Start recording to file once time is greater than this //40 for N, 3.6 for NH//9 for AN
extern bool allow_main_simulation;
extern double stim_time;
extern int N_slow;
extern int N_fast;
extern double voltage;
extern double max_dep_voltage;
extern int type;
extern bool i_bna_invest;
extern int solve_method;
extern const int l;
extern bool SKF;
extern bool blockNa;
extern bool blockCa;
extern int answer;
extern int answer2;
extern int answer3;
extern double factor_block;
extern double stim_current;
extern double coarse_time_step;
extern double fine_time_step ;
extern double switch_to_fine;
extern bool am_open_fine;
extern bool n_open_fine;
extern bool an_open_fine;
extern bool nh_open_fine;
extern double total_time_taken;
extern double total_time_steps;
extern double time_per_step_estimate;
extern bool import_am;
extern bool import_n;
extern bool import_an;
extern bool import_nh;
extern bool stimulate_test_cells;
extern double test_cell_stim_interval;
extern double test_stim_duration;
extern std::string import_file_prefix;
extern std::string all_files_suffix;
extern bool allow_am;
extern bool allow_an;
extern bool allow_nh;
extern bool allow_n;
extern double am_cell_unit_multiplier;
extern double am_cell_stim_multiplier;
extern bool analyse_indivdial_cell;
extern int individual_cell_index;
extern double first_stim_time;
extern bool clamp_test_cells;
extern double clamp_holding_voltage;
extern double clamp_peak_voltage;
extern double clamp_hold_start_time;
extern double clamp_peak_start_time;
extern double clamp_duration;
extern double stim_interval;
extern int print_adjuster;
extern bool clamp_multiple_voltages;
extern double first_clamp_voltage;
extern double last_clamp_voltage;
extern double clamp_voltage_step;
extern int multiple_clamp_type;
extern double triangle_peak_voltage;
extern double triangle_peak_time;
extern double triangle_return_to_hold_time;
extern bool done_indexes;
extern int number_stims;

extern double first_AM_activation_time;
extern double AM_activation_time; // Last AM cell (75th fastcell) before start of fast / slow pathways
extern double middle_fast_activation_time; // Middle (150th fast cell)fast pathway cell
extern double middle_slow_activation_time; // Middle (100th slow cell)slow pathway cell
extern double first_bundle_activation_time; // Start of penetratingbundle(first N cell after fast / slow pathway 226th fast cell)
extern double middle_bundle_activation_time; // Middle (288th fast cell)His Bundle cell
extern double activationPoint; // Reference pointfor activation potential activation(mV)
extern double start_monitoring_activation;
extern bool first_AM_activated;
extern bool AM_activated;
extern bool middle_fast_activated;
extern bool middle_slow_activated;
extern bool first_bundle_activated;
extern bool middle_bundle_activated;
extern bool all_activated;

#endif
