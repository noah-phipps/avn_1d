/*--------------------------------------------------------------------
-------- -
AVN Model main.cpp
21 / 03 / 2021	Fully rewritten by Noah PHIPPS and Gemma LAMB
--------------------------------------------------------------------
------ */

#include "av_node_2.h"
#include "am_cell.h"
#include"configuration.h"
#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include<ctime>
int main() {

	std::string file_name = "fast_cells";
	file_name.append(all_files_suffix);
	std::ofstream fast_cell_data{ file_name };

	file_name = "am_ions";
	file_name.append(all_files_suffix);
	std::ofstream am_ions{ file_name };

	file_name = "am_test_stim_current";
	file_name.append(all_files_suffix);
	std::ofstream am_test_stim_current{ file_name };


	file_name = "slow_cells";
	file_name.append(all_files_suffix);
	std::ofstream slow_cell_data{ file_name };

	file_name = "test_cells";
	file_name.append(all_files_suffix);
	std::ofstream  test_cell_data{ file_name };

	file_name = "am_test_currents";
	file_name.append(all_files_suffix);
	std::ofstream  am_test_currents{ file_name };

	file_name = "n_test_currents";
	file_name.append(all_files_suffix);
	std::ofstream  n_test_currents{ file_name };

	file_name = "an_test_currents";
	file_name.append(all_files_suffix);
	std::ofstream  an_test_currents{ file_name };

	file_name = "nh_test_currents";
	file_name.append(all_files_suffix);
	std::ofstream  nh_test_currents{ file_name };

	file_name = "fast_cell_details";
	file_name.append(all_files_suffix);
	std::ofstream  fast_cell_details{ file_name };

	file_name = "slow_cell_details";
	file_name.append(all_files_suffix);
	std::ofstream  slow_cell_details{ file_name };
	std::vector<bool> percentages;

	if (run_in_remote_configuration == false) {
		//Addition of SKF
		std::cout << "Add SKF? [1=yes, 2=no]\n";
		std::cin >> answer;
		std::cin.ignore();
		std::cin.clear();

		//Block
		std::cout << "Block? Na=1, Ca=2, none=3\n";
		std::cin >> answer2;
		std::cin.ignore();
		std::cin.clear();

		//Addition of ACh
		std::cout << "Add ACh? [0=no, 1=1uM, 2=100nM, 3=50nM, 4=30nM, 5=10nM]\n";
		std::cin >> answer3;
		std::cin.ignore();
		std::cin.clear();
	}

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
		std::cerr << "Incorrect input...\n\n\n";
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

	std::cout << "Beginning cell initialisation..." << std::endl;
	//Initialise array of cells, slow and fast pathway
	cell_base** fast_cells = new cell_base * [N_fast];
	cell_base** slow_cells = new cell_base * [N_slow];
	cell_base** test_cells = new cell_base * [4];
	bool test_cells_allowed[4];
	//Now generate cells just to test them; am, n, an, nh
	am_cell* test_am_cell = new am_cell();
	test_cells[0] = test_am_cell;
	test_cells_allowed[0] = allow_am;

	av_node_2* test_n_cell = new av_node_2(1,1);
	test_cells[1] = test_n_cell;
	test_cells_allowed[1] = allow_n;

	av_node_2* test_an_cell = new av_node_2(16,2);
	test_cells[2] = test_an_cell;
	test_cells_allowed[2] = allow_an;

	av_node_2* test_nh_cell = new av_node_2(19,3);
	test_cells[3] = test_nh_cell;
	test_cells_allowed[3] = allow_nh;

	//Set i stim for test cells to be 0 when starting
	for (int i{}; i < 4; i++) {
		(*test_cells[i]).set_i_stim(0);
	}
	std::cout << "\nCell initialisation complete!" << std::endl;
	//Now generate the cells in the slow pathway
	for (int cell_number = 0; cell_number < N_slow; cell_number++) {
		if (cell_number < 75) {
			if (import_am == true) {
				am_cell* cell = new am_cell(0);
				(*cell).set_coupling_conductance((1000E-9 - (500E-9 / (1 + exp((cell_number - 38) / -5))))); //jacks:500
				(*cell).set_g_na(.702);//NEW
				slow_cells[cell_number] = cell;
			}
			else {
				am_cell* cell = new am_cell();
				(*cell).set_coupling_conductance((1000E-9- (500E-9 / (1 + exp((cell_number - 38) / -5))))); //jacks:500
				(*cell).set_g_na(.702);//NEW
				slow_cells[cell_number] = cell;
			}
		}
		else {
			if (import_n == true) {
				av_node_2* cell = new av_node_2(1, 1);
				(*cell).set_coupling_conductance(300E-9); //jacks:300
				slow_cells[cell_number] = cell;
			}
			else {
				av_node_2* cell = new av_node_2(1);
				(*cell).set_coupling_conductance(300E-9); //jacks:300
				slow_cells[cell_number] = cell;
			}

		}
	}

	//Now generate cells in the fast pathway
	for (int cell_number = 0; cell_number < N_fast; cell_number++) {
		if (cell_number < 125) {
			if (import_am == true) {
				am_cell* cell = new am_cell(0);
				if (cell_number < 75) {
					(*cell).set_coupling_conductance(1000E-9);
					(*cell).set_g_na(.702);//NEW
				}
				else {
					(*cell).set_coupling_conductance((1000E-9 - (500E-9 / (1 +exp((cell_number - 120.5) / -5))))); //jacks:120.5
					(*cell).set_g_na(.702);//NEW
				}
				fast_cells[cell_number] = cell;
			}
			else {
				am_cell* cell = new am_cell();
				if (cell_number < 75) {
					(*cell).set_coupling_conductance(1000E-9);
					(*cell).set_g_na(.702);//NEW
				}
				else {
					(*cell).set_coupling_conductance((1000E-9 - (500E-9 / (1 +exp((cell_number - 120.5) / -5))))); //jacks:120.5
					(*cell).set_g_na(.702);//NEW
				}
				fast_cells[cell_number] = cell;
			}

		}
		else if (cell_number < 200) {
			if (import_an == true) {
				av_node_2* cell = new av_node_2(16, 2);
				(*cell).set_coupling_conductance(500E-9);
				//(*cell).set_g_na(253E-9);//NEW
				fast_cells[cell_number] = cell;
			}
			else {
				av_node_2* cell = new av_node_2(16);
				(*cell).set_coupling_conductance(500E-9);
				//(*cell).set_g_na(253E-9);//NEW
				fast_cells[cell_number] = cell;
			}

		}
		else if (cell_number >= 200 && cell_number < 225) {
			if (import_n == true) {
				av_node_2* cell = new av_node_2(1, 1);
				(*cell).set_coupling_conductance(300E-9);
				(*cell).set_g_na(3.2E-13 / (1 +exp((cell_number + 25.0 - 238.0) / 2.5))); //jacks: 5 //CHANGE FROM 5E-13 TO 2.53E-9
				fast_cells[cell_number] = cell;
			}
			else {
				av_node_2* cell = new av_node_2(1);
				(*cell).set_coupling_conductance(300E-9);
				(*cell).set_g_na(3.2E-13 / (1 +exp((cell_number + 25.0 - 238.0) / 2.5))); //jacks: 5//CHANGE FROM 5E-13 TO 2.53E-9
				fast_cells[cell_number] = cell;
			}

		}
		else {
			if (import_nh == true) {
				av_node_2* cell = new av_node_2(19, 3);
				if (cell_number < 250) {
					(*cell).set_coupling_conductance(300E-9);
					(*cell).set_g_na(4E-13 / (1 +exp((cell_number + 25.0 - 263.0) / -2.5))); //jacks orig:5//CHANGE FROM 5E-13 TO 2.53E-9
				}
				else {
					(*cell).set_coupling_conductance(500E-9); //jacks orig: 500
					//(*cell).set_g_na(253E-9);//NEW
				}
				fast_cells[cell_number] = cell;
			}
			else {
				av_node_2* cell = new av_node_2(19);
				if (cell_number < 250) {
					(*cell).set_coupling_conductance(300E-9);
					(*cell).set_g_na(4E-13 / (1 + exp((cell_number + 25.0 - 263.0) / -2.5))); //jacks orig:5//CHANGE FROM 5E-13 TO 2.53E-9
				}
				else {
					(*cell).set_coupling_conductance(500E-9); //jacks orig: 500
					//(*cell).set_g_na(253E-9);//NEW
				}
				fast_cells[cell_number] = cell;
			}

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
	for (int i{}; i < N_fast; i++) {
		fast_cell_details << (*fast_cells[i]).get_cell_type() << " \t " << (*fast_cells[i]).get_coupling_conductance() << " \t " << (*fast_cells[i]).get_g_na() << " \t " << (*fast_cells[i]).get_coupling_conductance() << std::endl;
	}
	for (int i{}; i < N_slow; i++) {
		slow_cell_details << (*slow_cells[i]).get_cell_type() << " \t " << (*slow_cells[i]).get_coupling_conductance() << " \t " << (*slow_cells[i]).get_g_na() << " \t " << (*slow_cells [i] ).get_coupling_conductance() << std::endl;
	}
	//INITIALISE and estimate sim  time
	double time = 0;
	int size = 0;//Number of timesteps in simulation
	std::cout << "\nEstimating simulation time..." << std::endl;
	while (time <= sim_time) {
		size++;
		time = time + time_step;
	}
	time = 0;
	total_time_steps = size;
	std::chrono::time_point<std::chrono::system_clock> time_right_now = std::chrono::system_clock::now();
	std::time_t t_c = std::chrono::system_clock::to_time_t(time_right_now + std::chrono::seconds(static_cast<int>(total_time_steps * time_per_step_estimate)));
	std::cout << "\nOperation complete...\nEstimated time to complete simulation is " << total_time_steps * time_per_step_estimate << " [secs], or " << total_time_steps * time_per_step_estimate / 60 << " [mins]." << std::endl;
	//std::cout <<"Estimated completion time is "<< std::put_time(std::localtime(&t_c), "%F %T.\n") << std::endl;
	std::cout << "Updates will be given every 10% " << std::endl << std::endl;

	//Initialise array counter
	int array_counter = 0;
	double deltaS = 0.4; //orig = 0.35

	//START SIMULATION
	std::cout << "Starting simulation...";
	std::chrono::steady_clock::time_point sim_start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point percent_start = std::chrono::steady_clock::now();
	int test_cell_stim_counter[4];
	test_cell_stim_counter[0] = 0;
	test_cell_stim_counter[1] = 0;
	test_cell_stim_counter[2] = 0;
	test_cell_stim_counter[3] = 0;

	while (time <= sim_time) {

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Do the test cells simulation here
		if (allow_test_cells == true) {
			for (int i{}; i < 4; i++) {
				if (test_cells_allowed[i] == true) {
					if (stimulate_test_cells == false && clamp_test_cells == false) {
						(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
						(*test_cells[i]).calc_vm(time_step, solve_method, false);
					}
					else if (clamp_test_cells == true) {
						if (time > clamp_duration + clamp_peak_start_time) {
							(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
							(*test_cells[i]).calc_vm(time_step, solve_method, false);
						}
						else if (time > clamp_peak_start_time) {
							(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
							(*test_cells[i]).set_vm(clamp_peak_voltage);
						}
						else if (time > clamp_hold_start_time) {
							(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
							(*test_cells[i]).set_vm(clamp_holding_voltage);
						}
						else {
							(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
							(*test_cells[i]).calc_vm(time_step, solve_method, false);
						}
					}
					else {
						if (time >= first_stim_time + test_cell_stim_counter[i] * test_cell_stim_interval) {
							(*test_cells[i]).set_i_stim(stim_current);
							if (i == 0) {
								(*test_cells[i]).set_i_stim(stim_current * am_cell_unit_multiplier * am_cell_stim_multiplier);
							}
							if (time >= first_stim_time + test_stim_duration + (test_cell_stim_counter[i] * test_cell_stim_interval)) {
								(*test_cells[i]).set_i_stim(0);
								(test_cell_stim_counter[i]) += 1;
							}
						}
						(*test_cells[i]).calc_i_all(time_step, solve_method, 0);
						(*test_cells[i]).calc_vm(time_step, solve_method, false);
					}
				}
			}

			if (array_counter % 2000 == 0) {
				//cout << "array counter is " << array_counter << endl;
				test_cell_data << time << "\t";
				if (analyse_indivdial_cell == false) {
					for (int i = 0; i < 4; i++) {
						test_cell_data << (*test_cells[i]).get_vm() << "\t";
					}
				}
				else {
					double dvdt = -((*test_cells[individual_cell_index]).get_total_ion(false) + (*test_cells[individual_cell_index]).get_i_stim()) / (*test_cells[individual_cell_index]).get_cm();
					test_cell_data << (*test_cells[individual_cell_index]).get_vm() << "\t" << dvdt;
				}

				(*test_cells[0]).print_currents(am_test_currents, time, 2);
				(*test_cells[1]).print_currents(n_test_currents, time, 1);
				(*test_cells[2]).print_currents(an_test_currents, time, 16);
				(*test_cells[3]).print_currents(nh_test_currents, time, 19);
				(*test_cells[0]).print_ions(am_ions, time);
				am_test_stim_current << time << "\t" << (*test_cells[0]).get_i_stim() << std::endl;
				test_cell_data << std::endl;
			}
		}
		//end test cells simulation
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (allow_main_simulation == true) {
			bool i_bna_zero = false;
			if (i_bna_invest) {
				i_bna_zero = true;
			}
			stim_current = 0;
			//control stim time
			for (int noStim = 0; noStim < 200; noStim++) {
				if (time > (first_stim_time + noStim * deltaS) && time < (first_stim_time + noStim * deltaS) + stim_time) {
					stim_current = -1.2e-9;
				}
			}
			//Loop over fast pathway
			for (int i = 0; i < N_fast; i++) {
				(*fast_cells[i]).set_i_stim(0.0);
				(*fast_cells[i]).calc_i_all(time_step, solve_method, l);
				bool stim = false;
				if (i == 0) {
					double cell_current = (*fast_cells[i]).get_coupling_conductance() * ((*fast_cells[i]).get_vm() - (*fast_cells[i + 1]).get_vm());
					if ((*fast_cells[i]).get_cell_type() == 2) {
						(*fast_cells[i]).set_i_stim(stim_current * am_cell_stim_multiplier * am_cell_unit_multiplier);
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
						(*fast_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
						(*fast_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
						(*fast_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
						(*fast_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
				if (i == 0){
					double cell_current = (*slow_cells[i]).get_coupling_conductance();
					cell_current *= (2 * (*slow_cells[i]).get_vm() - (*fast_cells[74]).get_vm() - (*slow_cells[i + 1]).get_vm());
					cell_current +=
						((*slow_cells[i + 1]).get_coupling_conductance() - (*fast_cells[74]).get_coupling_conductance()) * ((*fast_cells[74]).get_vm() - (*slow_cells[i + 1]).get_vm()) / 4;
					if ((*slow_cells[i]).get_cell_type() == 2) {
						(*slow_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
						(*slow_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
						(*slow_cells[i]).set_i_stim(cell_current * am_cell_unit_multiplier);
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
				fast_cell_data << time << "\t";
				for (int i = 0; i < N_fast / 5; i++) {
					double AP_shifter = (*fast_cells[i * 5]).get_vm() - (0.01 * i);
					fast_cell_data << AP_shifter << "\t";
				}
				slow_cell_data << time << "\t";
				for (int i = 0; i < N_slow / 5; i++) {
					double AP_shifter = (*slow_cells[i * 5]).get_vm() - (0.01 * i);
					slow_cell_data << AP_shifter << "\t";
				}
				fast_cell_data << std::endl;
				slow_cell_data << std::endl;
			}
		}
		array_counter++;
		double percent = time / sim_time;
		for (double j = 1; j <= 10; j++) {
			if ((j / 10) > percent - 0.000005 && (j /
				10) < percent + 0.000005) {
				if (percentages[static_cast<int>(j)] == false) {
					std::cout << "\n\n";
					std::cout << j * 10 << "% complete" << std::endl;
					std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
					std::cout << "Time for this 10 percent: " << std::chrono::duration_cast<std::chrono::minutes>(end - percent_start).count() << " [mins]" << ", or " << std::chrono::duration_cast<std::chrono::seconds>(end - percent_start).count() << " [secs]" << std::endl;
					std::cout << "Time for total simulation so far:  " << std::chrono::duration_cast<std::chrono::minutes> (end - sim_start).count() << " [mins]" << ", or " << std::chrono::duration_cast<std::chrono::seconds>(end - sim_start).count() << " [secs]" << std::endl;
					percent_start = std::chrono::steady_clock::now();
					percentages[static_cast<int>(j)] = true;
					total_time_taken = std::chrono::duration<double>(end - sim_start).count();
				}
			}
		}
		time += time_step;
	}

	std::cout << "\n\nSimulation complete! Time for total simulation: " << total_time_taken << " [secs]" << std::endl;
	std::cout << "Time per time step on average: " << total_time_taken / total_time_steps << " [secs]" << std::endl;

	//Now export any parameters if necessary
	std::cout << "\nNow exporting test cells for initialisation..." << std::endl;
	for (int i{}; i < 4; i++) {
		test_cells[i]->export_cell(i);
	}
	std::cout << "\nExport complete!" << std::endl;
	std::cout << "\n\n\nEND OF SIMULATION\n\n\n";
}