#include"configuration.h"




//Parameters that need to be configured for the simulation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GENERAL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Simulation parameters
double sim_time = 5;//Time for whole simulation //50 for N, 6 for NH //11.5 for AN
double start_record = 0; //Start recording to file once time is greater than this //40 for N, 3.6 for NH//9 for AN

bool allow_main_simulation{ false };

double stim_time = 0.001;
int N_slow = 200; //200
int N_fast = 325; //325

double voltage = 0;
double max_dep_voltage; //Maximum depolarizing voltage

int type = 0;
//SET to TRUE to set I_bna to zero
bool i_bna_invest = false;
int solve_method = 1;
int l = 0;
bool SKF = false;
bool blockNa = false;
bool blockCa = false;
int answer = 2;
int answer2 = 3;
int answer3 = 0;
double factor_block;// = 1;

double stim_current = 0;


//Timestep details
double coarse_time_step = 5E-8;//Time step used initially
double fine_time_step = 5E-8;//Time step switched to if required
double switch_to_fine = 100;//Time to switch from coarse to fine at, set to longer than sim_time to avoid

bool am_open_fine{ false };
bool n_open_fine{ false };
bool an_open_fine{ false };
bool nh_open_fine{ false };

double total_time_taken{};
double total_time_steps{};
double time_per_step_estimate{ 2.5E-5 };
