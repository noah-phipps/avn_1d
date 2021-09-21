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

double sim_time = 30;//Time for whole simulation //50 for N, 6 for NH //11.5 for AN
double start_record = 0; //Currently not implemented, time at which data recording can begin

int number_stims = 0;//Use 20 as default, number of stimulations in the simulation

bool allow_main_simulation{ true }; //Allow the main simulation to run
bool allow_test_cells{ false }; //Allow the individual uncoupled test cells to run

double stim_time = 0.001; //Duration of the stimulations
double stim_current = (-1.2E-9);//-1.2E-9
double first_stim_time = 90.1;
double stim_interval = 0.5;

std::string import_file_prefix{ "import_test_" };//Prefix for import files for initialising simulation
std::string all_files_suffix{ "_original.txt" };//Suffix to denote version of files (Used when running many versions on remote HPC)

//Timestep details
double coarse_time_step = 5E-6;//Time step used initially
double fine_time_step = 5E-8;//Time step switched to if required
double switch_to_fine = 100;//Time to switch from coarse to fine at, set to longer than sim_time to avoid

double time_per_step_estimate{ .00248293 };//Estimate length of simulation given a previous time per timestep result 

double am_cell_unit_multiplier{ 1E12 }; //1E12
double am_cell_stim_multiplier{ 1.666666 };//Changes to 2nA, as required by protocol

int print_adjuster{ 2000 };//Adjusts how many timesteps it is between each printing to file

double activationPoint{ -30E-3 }; // Reference point for activation potential activation
double start_monitoring_activation = 3;//Time at which to start monitoring for activation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INITIALISATION PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Allow or block initialisation of pathways using import files from previous simulations
bool import_am{ true };
bool import_n{ true };
bool import_an{ true };
bool import_nh{ true };

//If performing analysis on a single test cell to get parameters; test_cells_ .txt will be (time \t voltage \t dvdt) (dvdt currently incorrect, but god enough for peak analysis)
bool analyse_indivdial_cell{ false };
//Set the individual cell to analyse; index is for the test cell array, so 0=am, 1=n, 2=an, 3=nh
int individual_cell_index{ 0 };

int N_slow = 200; //Number of cells in the slow pathway
int N_fast = 325; //Number of cells in the fast pathway

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TEST CELL PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Multiple clamps
bool clamp_multiple_voltages{ false };
double first_clamp_voltage{ -40E-3 };
double last_clamp_voltage{ 40E-3 };
double clamp_voltage_step{ 1E-3 };
int multiple_clamp_type{ 0 };//0 for standard pulse, 1 for triangular
double triangle_peak_voltage{ 35E-3 };
double triangle_peak_time{ 1.03194 };
double triangle_return_to_hold_time{ 1.20106 };

//Both types of clamps
double clamp_duration{ 300E-3 };
double clamp_hold_start_time{ 0.5 };
double clamp_peak_start_time{ 1 };
double clamp_holding_voltage{ -50E-3 };

//Single clamp
bool clamp_test_cells{ false };
double clamp_peak_voltage{ -80E-3 };

//Stimulations
bool stimulate_test_cells{ true };//Allow stimulation of the test cells
double test_cell_stim_interval{ 0.5 };//Control interval between stimulations
double test_stim_duration{ 0.001 };//Control stimulation duration

//Allowing cells to run
bool allow_am{ true };
bool allow_an{ true };
bool allow_nh{ true };
bool allow_n{ true };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BLOCKING PARAMETERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SKF = true;
int answer = 0;//1 for SKF

bool blockNa = false;
bool blockCa = false;
bool i_bna_invest = false; //Enable blocking of ibna if true
double factor_block;//Factor by which Ca and Na are blocked; needs to be configured to allow independent factors, usually set via command line
const int l = 0;//Controls ACh concentration; usually set via command line
int answer3 = 0;
//0 for 0, 1 for 10-6, 2 for 10-7, 3 for .5*10-7, 4 for .3*10-7, 5 for 10-8

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES THAT NEED TO BE DECLARED BUT NOT CONFIGURED
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool am_open_fine{ false };
bool n_open_fine{ false };
bool an_open_fine{ false };
bool nh_open_fine{ false };

bool done_indexes{ false };

double total_time_taken{};
double total_time_steps{};


int answer2 = 3;


int solve_method = 1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ACTIVATION PARAMETERS INITIALISATION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double first_AM_activation_time{ 0 };
 double AM_activation_time{ 0 }; // Last AM cell (75th fastcell) before start of fast / slow pathways
 double middle_fast_activation_time{ 0 }; // Middle (150th fast cell)fast pathway cell
 double middle_slow_activation_time{ 0 }; // Middle (100th slow cell)slow pathway cell
 double first_bundle_activation_time{ 0 }; // Start of penetratingbundle(first N cell after fast / slow pathway 226th fast cell)
 double middle_bundle_activation_time{ 0 }; // Middle (288th fast cell)His Bundle cell

 bool first_AM_activated{ false };
 bool AM_activated{ false };
 bool middle_fast_activated{ false };
 bool middle_slow_activated{ false };
 bool first_bundle_activated{ false };
 bool middle_bundle_activated{ false };
 bool all_activated{ false };
