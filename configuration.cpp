/*--------------------------------------------------------------------
-------- -
AVN Model Configuration File
21 / 03 / 2021	Created by Noah PHIPPS and Gemma LAMB
--------------------------------------------------------------------
------ */
#include"configuration.h"

//Parameters that need to be configured for the simulation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GENERAL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool run_in_remote_configuration{ true };//True for running remotely on HPC etc, won't allow user input

double sim_time = 2;//Time for whole simulation //50 for N, 6 for NH //11.5 for AN
double start_record = 0; //Currently not implemented, time at which data recording can begin

bool allow_main_simulation{ false }; //Allow the main simulation to run
bool allow_test_cells{ true }; //Allow the individual uncoupled test cells to run

double stim_time = 0.001; //Duration of the stimulations
double stim_current = (-2.5E-9);//-1.2E-9
double first_stim_time = .5;

std::string import_file_prefix{ "import_test_" };//Prefix for import files for initialising simulation
std::string all_files_suffix{ "_original.txt" };//Suffix to denote version of files (Used when running many versions on remote HPC)

//Timestep details
double coarse_time_step = 5E-7;//Time step used initially
double fine_time_step = 5E-8;//Time step switched to if required
double switch_to_fine = 100;//Time to switch from coarse to fine at, set to longer than sim_time to avoid

double time_per_step_estimate{ 1.96E-5 };//Estimate length of simulation given a previous time per timestep result 

double am_cell_unit_multiplier{ 1E12 }; //1E12
double am_cell_stim_multiplier{ 1 };//4.2, 3.5
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INITIALISATION PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Allow or block initialisation of pathways using import files from previous simulations
bool import_am{ false };
bool import_n{ false };
bool import_an{ false };
bool import_nh{ false };

//If performing analysis on a single test cell to get parameters; test_cells_ .txt will be (time \t voltage \t dvdt) (dvdt currently incorrect, but god enough for peak analysis)
bool analyse_indivdial_cell{ true };
//Set the individual cell to analyse; index is for the test cell array, so 0=am, 1=n, 2=an, 3=nh
int individual_cell_index{ 0 };

int N_slow = 200; //Number of cells in the slow pathway
int N_fast = 325; //Number of cells in the fast pathway

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TEST CELL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool stimulate_test_cells{ true };//Allow stimulation of the test cells
double test_cell_stim_interval{ 0.5 };//Control interval between stimulations
bool clamp_test_cells{ false };
double clamp_holding_voltage{ -90E-3 };
double clamp_peak_voltage{ 30E-3 };
double clamp_hold_start_time{ 1 };
double clamp_peak_start_time{ 1.5 };
double clamp_duration{ 50E-3 };
double test_stim_duration{ 0.001 };//Control stimulation duration

bool allow_am{ true };
bool allow_an{ false };
bool allow_nh{ false };
bool allow_n{ false };

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