#include "av_node_2.h"
#include "output_files.h"
#include "am_cell.h"
#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include<ctime>
using namespace std;
int main() {
	vector<bool> percentages;
	//Addition of SKF
	/*
	cout << "Add SKF? [1=yes, 2=no]\n";
	cin >> answer;
	cin.ignore();
	cin.clear();

	//Block
	cout << "Block? Na=1, Ca=2, none=3\n";
	cin >> answer2;
	cin.ignore();
	cin.clear();

	//Addition of ACh
	cout << "Add ACh? [0=no, 1=1uM, 2=100nM, 3=50nM, 4=30nM, 5=10nM]\n";
	cin >> answer3;
	cin.ignore();
	cin.clear();
	*/
	//If adding ACh
	if (answer3 == 0) {
		l = 0;
	}
	else if (answer3 == 1) {
		l = 1;
	}
	else if (answer3 == 2) {
		l = 2;
	}
	else if (answer3 == 3) {
		l = 3;
	}
	else if (answer3 == 4) {
		l = 4;
	}
	else if (answer3 == 5) {
		l = 5;
	}
	else {
		cerr << "incorrect input...\n\n\n";
		exit(1);
	}

	//If adding SKF
	if (answer == 1) {
		SKF = true;
		solve_method = 2;
	}

	//If blocking
	if (answer2 == 1) {
		blockNa = true;
		std::cout << "Block Na by factor:\n";
		std::cin >> factor_block;
	}
	else if (answer2 == 2) {
		blockCa = true;
		std::cout << "Block Ca by factor:\n";
		std::cin >> factor_block;
	}

	//Populate percentages vector
	for (int k{ 0 }; k < 11; k++) {
		percentages.push_back(false);
	}

	cout << "Beginning cell initialisation..." << endl;
	//Initialise array of cells, slow and fast pathway
	cell_base** fast_cells = new cell_base * [N_fast];
	cell_base** slow_cells = new cell_base * [N_slow];
	cell_base** test_cells = new cell_base * [4];

	//Now generate cells just to test them; am, n, an, nh
	am_cell* test_am_cell = new am_cell(0);
	test_cells[0] = test_am_cell;

	av_node_2* test_n_cell = new av_node_2(1);
	test_cells[1] = test_n_cell;

	av_node_2* test_an_cell = new av_node_2(16);
	test_cells[2] = test_an_cell;

	av_node_2* test_nh_cell = new av_node_2(19);
	test_cells[3] = test_nh_cell;

	for (int i{}; i < 4; i++) {
		(*test_cells[i]).set_i_stim(0);
	}
	cout << "\nCell initialisation complete!" << endl;
	//Now generate the cells in the slow pathway
	for (int cell_number = 0; cell_number < N_slow;
		cell_number++) {
		if (cell_number < 75) {
			am_cell* cell = new am_cell();
			(*cell).set_coupling_conductance((1000E-9
				- (500E-9 / (1 + exp((cell_number - 38) / -5))))); //jacks:500
			slow_cells[cell_number] = cell;
		}
		else {
			av_node_2* cell = new av_node_2(1);
			(*cell).set_coupling_conductance(300E-9); //jacks:300
			slow_cells[cell_number] = cell;
		}
	}

	//Now generate cells in the fast pathway
	for (int cell_number = 0; cell_number < N_fast;
		cell_number++) {
		if (cell_number < 125) {
			am_cell* cell = new am_cell();
			if (cell_number < 75) {
				(*cell).set_coupling_conductance(1000E-9);
			}
			else {
				(*cell).set_coupling_conductance((1000E-9 - (500E-9 / (1 +
					exp((cell_number - 120.5) / -5))))); //jacks:120.5
			}
			fast_cells[cell_number] = cell;
		}
		else if (cell_number < 200) {
			av_node_2* cell = new av_node_2(16);
			(*cell).set_coupling_conductance(500E-9);
			fast_cells[cell_number] = cell;
		}
		else if (cell_number >= 200 && cell_number < 225) {
			av_node_2* cell = new av_node_2(1);
			(*cell).set_coupling_conductance(300E-9);
			(*cell).set_g_na(5E-13 / (1 +
				exp((cell_number + 25 - 238) / 2.5))); //jacks: 5
			fast_cells[cell_number] = cell;
		}
		else {
			av_node_2* cell = new av_node_2(19);
			if (cell_number < 250) {
				(*cell).set_coupling_conductance(300E-9);
				(*cell).set_g_na(5E-13 / (1 +
					exp((cell_number + 25 - 263) / -2.5))); //jacks orig:5
			}
			else {
				(*cell).set_coupling_conductance(5000E-9); //jacks orig: 500
			}
			fast_cells[cell_number] = cell;
		}
	}

	//Set time step
	double time_step = coarse_time_step;

	//Set SKF values, and blocking, for slow pathway
	for (int i = 0; i < N_slow; i++) {
		if ((*slow_cells[i]).get_cell_type() == 1) {
			if (SKF) {
				(*slow_cells[i]).set_g_ca(1.05E-08);
				(*slow_cells[i]).set_g_kr(0.7e-09);
				(*slow_cells[i]).set_g_st(2.15E-09);
				(*slow_cells[i]).set_g_b(1.3E-09);
				(*slow_cells[i]).set_p_max(6.4E-10);
				(*slow_cells[i]).set_k_naca(2.14E-09);
				(*slow_cells[i]).set_P_na(5.78E-16);
			}
		}
		if (blockNa) {
			(*slow_cells[i]).block_na(factor_block);
		}
		if (blockCa) {
			(*slow_cells[i]).block_ca(factor_block);
		}
	}

	//Set SKF values, and blocking, for fast pathway
	for (int i = 0; i < N_fast; i++) {
		if ((*fast_cells[i]).get_cell_type() == 1) {
			if (SKF) {
				(*fast_cells[i]).set_g_ca(1.05E-08);
				(*fast_cells[i]).set_g_kr(0.7e-09);
				(*fast_cells[i]).set_g_st(2.15E-09);
				(*fast_cells[i]).set_g_b(1.3E-09);
				(*fast_cells[i]).set_p_max(6.4E-10);
				(*fast_cells[i]).set_k_naca(2.14E-09);
				(*fast_cells[i]).set_P_na(5.78E-16);
			}
		}
		if (blockNa) {
			(*fast_cells[i]).block_na(factor_block);
		}
		if (blockCa) {
			(*fast_cells[i]).block_ca(factor_block);
		}
	}

	//i_bna_invest = true;
	//INITIALISE
	double time = 0;
	int size = 0;//Number of timesteps in simulation
	cout << "\nEstimating simulation time..."<<endl;
	while (time <= sim_time) {
		size++;
		time = time + time_step;
	}
	time = 0;
	total_time_steps = size;
	std::chrono::time_point<std::chrono::system_clock> time_right_now = std::chrono::system_clock::now();
	std::time_t t_c = std::chrono::system_clock::to_time_t(time_right_now + std::chrono::seconds(static_cast<int>(total_time_steps * time_per_step_estimate)));
	cout << "\nOperation complete...\nEstimated time to complete simulation is " << total_time_steps * time_per_step_estimate << " [secs], or " << total_time_steps * time_per_step_estimate / 60 << " [mins]." << endl;
	cout <<"Estimated completion time is "<< std::put_time(std::localtime(&t_c), "%F %T.\n") << endl;

	cout<<"Updates will be given every 10\ % "<<endl<<endl;


	//Arrays, one value for each timestep
	//double* time_array = new double[size];
	//double* first_AM_vm = new double[size]; // First AM cell(1st fast cell) for reference
	//double* AM_vm = new double[size]; // Last AM cell (75thfast cell) before start of fast / slow pathways
	//double* SP_vm = new double[size]; // Middle slow pathwaycell
	//double* FP_vm = new double[size]; // Middle fast pathwaycell
	//double* PB_vm = new double[size]; // Start of penetratingbundle
	//double* HB_vm = new double[size]; // Middle His Bundlecell
	//double* SP_end_vm = new double[size]; // End of the slowpathway
	//double* vm_array_atrium_start = new double[size];
	//double* vm_array_atrium_end = new double[size];
	//double* vm_array_slow_start = new double[size];
	//double* vm_array_slow_end = new double[size];
	//double* diff_vm_array = new double[size];
	am_cell cell;


	//Initialise array counter
	int array_counter = 0;
	double deltaS = 0.35; //orig = 0.35






//START SIMULATION
	cout << "Starting simulation...";
	std::chrono::steady_clock::time_point sim_start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point percent_start = std::chrono::steady_clock::now();

	while (time <= sim_time) {

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Do the test cells simulation here
		for (int i{}; i < 4; i++) {
			(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
			(*test_cells[i]).calc_vm(time_step, solve_method, false);
		}

	if (array_counter % 2000 == 0) {
		//cout << "array counter is " << array_counter << endl;
		fprintf(test_cell_data, "%g\t", time);
		for (int i = 0; i < 4; i++) {
			fprintf(test_cell_data, "% g\t", (*test_cells[i]).get_vm());
		}
		fprintf(test_cell_data, "\n");
	}
		//end test cells simulation
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (allow_main_simulation == true) {
		bool i_bna_zero = false;
		if (i_bna_invest) {
			i_bna_zero = true;
		}

		//control stim time
		for (int noStim = 0; noStim < 20; noStim++) {
			if (time > (0.1 + noStim * deltaS) && time <
				(0.1 + noStim * deltaS) + stim_time) {
				stim_current = -1.2e-9;
			}
		}

		//Loop over fast pathway
		for (int i = 0; i < N_fast; i++) {
			(*fast_cells[i]).set_i_stim(0);
			(*fast_cells[i]).calc_i_all(time_step, solve_method, l);
			bool stim = false;
			if (i == 0) {
				//double cell_current =(*fast_cells[i]).get_coupling_conductance()* ((*fast_cells[i]).get_vm() - (*fast_cells[i + 1]).get_vm());
				if ((*fast_cells[i]).get_cell_type() == 2) {
					(*fast_cells[i]).set_i_stim(stim_current * 2.5E12);
				}
				else {
					(*fast_cells[i]).set_i_stim(stim_current);
				}
			}
			else if (i == 74) {
				// Due to three nearest neighbours
				double cell_current =
					(*fast_cells[i]).get_coupling_conductance() * (3 * (*fast_cells[i]).get_vm() - (*fast_cells[i - 1]).get_vm() - (*fast_cells[i + 1]).get_vm() - (*slow_cells[0]).get_vm());
				cell_current +=
					(((*fast_cells[i + 1]).get_coupling_conductance() - (*fast_cells[i - 1]).get_coupling_conductance()) * ((*fast_cells[i - 1]).get_vm() - (*fast_cells[i + 1]).get_vm())) / 4;
				cell_current +=
					(((*fast_cells[i + 1]).get_coupling_conductance() - (*slow_cells[0]).get_coupling_conductance()) * ((*slow_cells[0]).get_vm() - (*fast_cells[i + 1]).get_vm())) / 4;
				cell_current +=
					(((*slow_cells[0]).get_coupling_conductance() - (*fast_cells[i - 1]).get_coupling_conductance()) * ((*fast_cells[i - 1]).get_vm() - (*slow_cells[0]).get_vm())) / 4;
				if ((*fast_cells[i]).get_cell_type() == 2) {
					//Due to different AMcell units
					(*fast_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*fast_cells[i]).set_i_stim(cell_current);
				}
			}
			else if (i == 224) {
				double cell_current =
					(*fast_cells[i]).get_coupling_conductance() * (3 * (*fast_cells[i]).get_vm() - (*fast_cells[i - 1]).get_vm() - (*fast_cells[i + 1]).get_vm() - (*slow_cells[N_slow - 1]).get_vm());
				cell_current +=
					((*fast_cells[i + 1]).get_coupling_conductance() - (*fast_cells[i - 1]).get_coupling_conductance()) * ((*fast_cells[i - 1]).get_vm() + (*fast_cells[i + 1]).get_vm()) / 4;
				cell_current +=
					((*fast_cells[i + 1]).get_coupling_conductance() - (*slow_cells[N_slow - 1]).get_coupling_conductance()) * ((*slow_cells[N_slow - 1]).get_vm() + (*fast_cells[i + 1]).get_vm()) / 4;
				cell_current +=
					((*slow_cells[N_slow - 1]).get_coupling_conductance() - (*fast_cells[i - 1]).get_coupling_conductance()) * ((*fast_cells[i - 1]).get_vm() + (*slow_cells[N_slow - 1]).get_vm()) / 4;
				if ((*fast_cells[i]).get_cell_type() == 2) {
					//Due to different AMcell units
					(*fast_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*fast_cells[i]).set_i_stim(cell_current);
				}
			}
			else if (i != 0 && i != 224 && i != (N_fast - 1) && i != 74) {
				double cell_current =
					(*fast_cells[i]).get_coupling_conductance() * (2 * (*fast_cells[i]).get_vm() - (*fast_cells[i - 1]).get_vm() - (*fast_cells[i + 1]).get_vm());
				cell_current +=
					((*fast_cells[i + 1]).get_coupling_conductance() - (*fast_cells[i - 1]).get_coupling_conductance()) * ((*fast_cells[i - 1]).get_vm() - (*fast_cells[i + 1]).get_vm()) / 4;
				if ((*fast_cells[i]).get_cell_type() == 2) {
					(*fast_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*fast_cells[i]).set_i_stim(cell_current);
				}
			}
			else if (i == N_fast - 1) {
				//Ghost cell with same vm as i
				double cell_current =
					(*fast_cells[i]).get_coupling_conductance() * ((*fast_cells[i]).get_vm() - (*fast_cells[i - 1]).get_vm());
				cell_current +=
					((*fast_cells[i]).get_coupling_conductance() - (*fast_cells[i - 1]).get_coupling_conductance()) * ((*fast_cells[i - 1]).get_vm() - (*fast_cells[i]).get_vm()) / 4;
				if ((*fast_cells[i]).get_cell_type() == 2) {
					(*fast_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*fast_cells[i]).set_i_stim(cell_current);
				}
			}
		}

		//Loop over slow pathway
		for (int i = 0; i < N_slow; i++) {
			(*slow_cells[i]).set_i_stim(0);
			(*slow_cells[i]).calc_i_all(time_step, solve_method, l);
			if (i == 0) {
				double cell_current =
					(*slow_cells[i]).get_coupling_conductance() * (2 * (*slow_cells[i]).get_vm() - (*fast_cells[74]).get_vm() - (*slow_cells[i + 1]).get_vm());
				cell_current +=
					((*slow_cells[i + 1]).get_coupling_conductance() - (*fast_cells[74]).get_coupling_conductance()) * ((*fast_cells[74]).get_vm() - (*slow_cells[i + 1]).get_vm()) / 4;
				if ((*slow_cells[i]).get_cell_type() == 2) {
					(*slow_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*slow_cells[i]).set_i_stim(cell_current);
				}
			}
			else if (i == (N_slow - 1)) {
				double cell_current =
					(*slow_cells[i]).get_coupling_conductance() * (2 * (*slow_cells[i]).get_vm() - (*slow_cells[i - 1]).get_vm() - (*fast_cells[224]).get_vm());
				cell_current +=
					((*fast_cells[224]).get_coupling_conductance() - (*slow_cells[i - 1]).get_coupling_conductance()) * ((*slow_cells[i - 1]).get_vm() - (*fast_cells[224]).get_vm()) / 4;
				double test = cell_current;
				if ((*slow_cells[i]).get_cell_type() == 2) {
					(*slow_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*slow_cells[i]).set_i_stim(cell_current);
				}
			}
			else {
				double cell_current =
					(*slow_cells[i]).get_coupling_conductance() * (2 * (*slow_cells[i]).get_vm() - (*slow_cells[i - 1]).get_vm() - (*slow_cells[i + 1]).get_vm());
				cell_current +=
					((*slow_cells[i + 1]).get_coupling_conductance() - (*slow_cells[i - 1]).get_coupling_conductance()) * ((*slow_cells[i - 1]).get_vm() - (*slow_cells[i + 1]).get_vm()) / 4;
				if (cell_current != 0) {
					double test = 0;
				}
				if ((*slow_cells[i]).get_cell_type() == 2) {
					(*slow_cells[i]).set_i_stim(cell_current * 1000E9);
				}
				else {
					(*slow_cells[i]).set_i_stim(cell_current);
				}
			}
		}

		for (int i = 0; i < N_fast; i++) {
			(*fast_cells[i]).calc_vm(time_step, solve_method, i_bna_zero);
		}
		for (int i = 0; i < N_slow; i++) {
			(*slow_cells[i]).calc_vm(time_step, solve_method, i_bna_zero);
		}


		if (array_counter % 2000 == 0) {
			//cout << "array counter is " << array_counter << endl;
			fprintf(fast_cell_data, "%g\t", time);
			for (int i = 0; i < N_fast / 5; i++) {
				double AP_shifter = (*fast_cells[i * 5]).get_vm() - (0.01 * i);
				fprintf(fast_cell_data, "% g\t", AP_shifter);
			}
			fprintf(slow_cell_data, "%g\t", time);
			for (int i = 0; i < N_slow / 5; i++) {
				double AP_shifter = (*slow_cells[i * 5]).get_vm() - (0.01 * i);
				fprintf(slow_cell_data, "% g\t", AP_shifter);
			}
			fprintf(fast_cell_data, "\n");
			fprintf(slow_cell_data, "\n");
		}
		//Writing stuff to arrays


		//first_AM_vm[array_counter] =(*fast_cells[1]).get_vm();
		//AM_vm[array_counter] = (*fast_cells[74]).get_vm();
		//SP_vm[array_counter] = (*slow_cells[137]).get_vm();
		//FP_vm[array_counter] = (*fast_cells[174]).get_vm();
		//SP_end_vm[array_counter] = (*slow_cells[N_slow -1]).get_vm();
		//PB_vm[array_counter] = (*fast_cells[224]).get_vm();
		//HB_vm[array_counter] = (*fast_cells[288]).get_vm();
		//vm_array_atrium_start[array_counter] =(*fast_cells[0]).get_vm();
		//vm_array_slow_start[array_counter] =(*slow_cells[75]).get_vm();
		//vm_array_atrium_end[array_counter] =(*fast_cells[74]).get_vm();
		//vm_array_slow_end[array_counter] =(*slow_cells[N_slow - 1]).get_vm();
		//time_array[array_counter] = time;

		//Printing progress
	}
	array_counter++;
		double percent = time / sim_time;
		for (double j = 1; j <= 10; j++) {
			if ((j / 10) > percent - 0.000005 && (j /
				10) < percent + 0.000005) {
				if (percentages[j] == false) {
					std::cout << "\n\n";
					std::cout << j * 10 << "% complete"<<endl;
					std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
					std::cout << "Time for this 10 percent: " << std::chrono::duration_cast<std::chrono::minutes>(end - percent_start).count() << " [mins]" << ", or "<< std::chrono::duration_cast<std::chrono::seconds>(end - percent_start).count()<<" [secs]"<<endl;
					std::cout << "Time for total simulation so far:  " << std::chrono::duration_cast<std::chrono::minutes> (end - sim_start).count() << " [mins]" << ", or " << std::chrono::duration_cast<std::chrono::seconds>(end - sim_start).count() << " [secs]" << endl;
					percent_start= std::chrono::steady_clock::now();
					percentages[j] = true;
					total_time_taken = std::chrono::duration_cast<std::chrono::seconds>(end - sim_start).count();
				}
			}
		}
		time += time_step;
	}

	std::cout << "\n\nSimulation complete! Time for total simulation: " << total_time_taken << " [secs]"<< endl;
	std::cout << "Time per time step on average: " << total_time_taken / total_time_steps << " [secs]" << endl;


	//Now export any parameters if necessary
	cout << "\nNow exporting test cells for initialisation..." << endl;
	for (int i{}; i < 4; i++) {
		test_cells[i]->export_cell(i);
	}
	cout << "\nExport complete!" << endl;


	double first_AM_activation_time = 0;
	double AM_activation_time = 0; // Last AM cell (75th fastcell) before start of fast / slow pathways
	double SP_activation_time = 0; // Middle (100th slow cell)slow pathway cell
	double FP_activation_time = 0; // Middle (150th fast cell)fast pathway cell
	double PB_activation_time = 0; // Start of penetratingbundle(first N cell after fast / slow pathway 226th fast cell)
	double HB_activation_time = 0; // Middle (288th fast cell)His Bundle cell
	double SP_end_activation_time = 0;
	const double activationPoint = -30e-3; // Reference pointfor activation potential activation(mV)
	bool first_AM_activated(false), AM_activated(false),SP_activated(false), FP_activated(false), PB_activated(false),HB_activated(false), SP_end_activated(false);
	bool first_AM_over(false), AM_over(false), SP_over(false),FP_over(false), PB_over(false), HB_over(false), SP_end_over(false);
	double startRecording = 0.775; // Ignore the first 0.775seconds until system reaches a steady state
	bool successful = false;
	int noStimsMeasure = 1;

	/*
	for (int i = 0; i < size; i++) {
		if (time_array[i] > (deltaS * noStimsMeasure + 0.1)&& time_array[i] < (deltaS * (noStimsMeasure + 1) + 0.1)) {
			if (HB_vm[i] > 0 && !successful) {
				successful = true;
			}
		}
	}
	if (!successful) {
		noStimsMeasure++;
	}
	for (int i = 0; i < size; i++) {
		if (time_array[i] > (deltaS * noStimsMeasure) + 0.1) {
			if (first_AM_vm[0] > activationPoint && !first_AM_over) {
				if (first_AM_vm[i] <activationPoint) {
					first_AM_over = true;
				}
				first_AM_activated = false;
			}
			else { first_AM_over = true; }
			if (AM_vm[0] > activationPoint && !AM_over) {
				if (AM_vm[i] < activationPoint) {
					AM_over = true;
				}
				AM_activated = false;
			}
			else { AM_over = true; }
			if (SP_vm[0] > activationPoint && !SP_over) {
				if (SP_vm[i] < activationPoint) {
					SP_over = true;
				}
				SP_activated = false;
			}
			else { SP_over = true; }
			if (SP_end_vm[0] > activationPoint && !SP_end_over) {
				if (SP_end_vm[i] <activationPoint) {
					SP_end_over = true;
				}
				SP_end_activated = false;
			}
			else { SP_end_over = true; }
			if (FP_vm[0] > activationPoint && !FP_over) {
				if (FP_vm[i] < activationPoint) {
					FP_over = true;
				}
				FP_activated = false;
			}
			else { FP_over = true; }
			if (PB_vm[0] > activationPoint && !PB_over) {
				if (PB_vm[i] < activationPoint) {
					PB_over = true;
				}
				PB_activated = false;
			}
			else { PB_over = true; }
			if (HB_vm[0] > activationPoint && !HB_over) {
				if (HB_vm[i] < activationPoint) {
					HB_over = true;
				}
				HB_activated = false;
			}
			else { HB_over = true; }
			if (first_AM_vm[i] <= activationPoint &&first_AM_activated == false && first_AM_over) { // If membranepotential is less that activation potential store time
				first_AM_activation_time =time_array[i];
			}
			else { first_AM_activated = true; } //Once membrane potential has passed activation point action potentialis activatedand will stop storing time
			if (AM_vm[i] <= activationPoint &&AM_activated == false && AM_over) {
				AM_activation_time =time_array[i];
			}
			else { AM_activated = true; }
			if (SP_vm[i] <= activationPoint && SP_activated == false && SP_over) {
				SP_activation_time =time_array[i];
			}
			else { SP_activated = true; }
			if (SP_end_vm[i] <= activationPoint &&SP_end_activated == false && SP_end_over) {
				SP_end_activation_time =time_array[i];
			}
			else { SP_end_activated = true; }
			if (FP_vm[i] <= activationPoint &&FP_activated == false && FP_over) {
				FP_activation_time =time_array[i];
			}
			else { FP_activated = true; }
			if (PB_vm[i] <= activationPoint &&PB_activated == false && PB_over) {
				PB_activation_time =time_array[i];
			}
			else { PB_activated = true; }
			if (HB_vm[i] <= activationPoint &&HB_activated == false && HB_over) {
				HB_activation_time =time_array[i];
			}
			else { HB_activated = true; }
		}
	}
	*/
	cout << "Activation time of first AM cell = " <<first_AM_activation_time * 1000 - first_AM_activation_time * 1000 <<" ms\n";
	std::cout << "Activation time of last AM cell = " <<
		AM_activation_time * 1000 - first_AM_activation_time * 1000 << "ms\n";
	std::cout << "Activation time of middle fast cell = " <<
		FP_activation_time * 1000 - first_AM_activation_time * 1000 << "ms\n";
	std::cout << "Activation time of middle slow cell = " <<
		SP_activation_time * 1000 - first_AM_activation_time * 1000 << "ms\n";
	std::cout << "Activation time of end of slow pathway = " <<
		SP_end_activation_time * 1000 - first_AM_activation_time * 1000 << "ms\n";
	std::cout << "Activation time of first penetrating bundlecell = " << PB_activation_time * 1000 - first_AM_activation_time *
		1000 << " ms\n";
	std::cout << "Activation time of middle His bundle cell = "
		<< HB_activation_time * 1000 - first_AM_activation_time * 1000 << "ms\n";
	std::cout << "Atrial conduction velocity = " << ((7.5e-3) /
		(AM_activation_time - first_AM_activation_time)) * 1e2 << "cm/s" <<
		std::endl;
	std::cout << "Slow pathway conduction velocity = " <<
		((20e-3) / (SP_end_activation_time - AM_activation_time)) * 1e2 <<
		"cm/s or " << ((2e-3) / (SP_end_activation_time -
			AM_activation_time)) * 1e2 << "cm/s" << std::endl << std::endl;
	std::cout << "Fast pathway conduction velocity = " <<
		((15e-3) / (PB_activation_time - AM_activation_time)) * 1e2 << "cm/sor " << ((1.5e-3) / (PB_activation_time - AM_activation_time)) * 1e2
		<< "cm/s" << std::endl << std::endl;
	std::cout << "\n\n\nEND OF SIMULATION\n";
	std::cout << "enter...";
	std::cin >> ws;
	_fcloseall;
}