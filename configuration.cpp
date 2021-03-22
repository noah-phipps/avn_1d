/*--------------------------------------------------------------------
-------- -
AVN Model Configuration File
21 / 03 / 2021	Created by Noah PHIPPS 
--------------------------------------------------------------------
------ */
#include"configuration.h"

//Parameters that need to be configured for the simulation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GENERAL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool run_in_remote_configuration{ true };//True for running remotely on HPC etc, won't allow user input

double sim_time = 1;//Time for whole simulation //50 for N, 6 for NH //11.5 for AN
double start_record = 0; //Currently not implemented, time at which data recording can begin

bool allow_main_simulation{ true }; //Allow the main simulation to run
bool allow_test_cells{ true }; //Allow the individual uncoupled test cells to run

double stim_time = 0.001; //Duration of the stimulations
double stim_current = (-1.2E-9);

std::string import_file_prefix{ "import_test_" };//Prefix for import files for initialising simulation
std::string all_files_suffix{ "_original.txt" };//Suffix to denote version of files (Used when running many versions on remote HPC)

//Timestep details
double coarse_time_step = 5E-8;//Time step used initially
double fine_time_step = 5E-8;//Time step switched to if required
double switch_to_fine = 100;//Time to switch from coarse to fine at, set to longer than sim_time to avoid

double time_per_step_estimate{ 1.96E-5 };//Estimate length of simulation given a previous time per timestep result 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INITIALISATION PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Allow or block initialisation of pathways using import files from previous simulations
bool import_am{ true };
bool import_n{ true };
bool import_an{ true };
bool import_nh{ true };

int N_slow = 200; //Number of cells in the slow pathway
int N_fast = 325; //Number of cells in the fast pathway

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TEST CELL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool stimulate_test_cells{ true };//Allow stimulation of the test cells
double test_cell_stim_interval{ 0.4 };//Control interval between stimulations
double test_stim_duration{ 0.001 };//Control stimulation duration

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BLOCKING PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SKF = false;
bool blockNa = false;
bool blockCa = false;
bool i_bna_invest = false; //Enable blocking of ibna if true
double factor_block;//Factor by which Ca and Na are blocked; needs to be configured to allow independent factors, usually set via command line
int l = 0;//Controls ACh concentration; usually set via command line

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES THAT NEED TO BE DECLARED BUT NOT CONFIGURED
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool am_open_fine{ false };
bool n_open_fine{ false };
bool an_open_fine{ false };
bool nh_open_fine{ false };

double total_time_taken{};
double total_time_steps{};

int answer = 2;
int answer2 = 3;
int answer3 = 0;

int solve_method = 1;