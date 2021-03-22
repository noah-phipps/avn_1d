/*--------------------------------------------------------------------
-------- -
AV node cell action potential model
14 / 12 / 2007 Created by Shin INADA
11 / 04 / 2008 Modified by Shin INADA(add ACh sensitive current, added intracellular calciumdynamics)
07 / 11 / 2020 Modified by Noah PHIPPS & Gemma LAMB (Optimisation of currents with respect to experimental data)
21 / 03 / 2021 Modified by Noah PHIPPS (Removing depreceated C style code, optimising functions, formatting, generally rewritten)
--------------------------------------------------------------------
------ */
//Header files
#ifndef AV_NODE_2_H
#define AV_NODE_2_H
#include <iostream>
#include"configuration.h"
#include<float.h>
#include <math.h>
#include<sstream>
#include<fstream>
#include "cell_base.h"
#include <string>
//Definition of macro
#define SET_PARAMS(cm, centre, periphery)  (((cm) - 20.0e-12) / 45.0e-12 * ((periphery) - (centre)) + (centre))
//Atrioventricular node cell model
class av_node_2 : public cell_base {
	double act_l{}, fast_inact_l{}, slow_inact_l{};
	double fast_act_kr{}, slow_act_kr{}, inact_kr{};
	double act_to{}, fast_inact_to{}, slow_inact_to{};
	double g_f{}, act_f{};
	double act_st{}, inact_st{};
	double rev_b{};
	double rev_l{}, rev_st{};
	double rev_bna{};
	double act_na{}, fast_inact_na{}, slow_inact_na{};
	double i_na{}, i_l{}, i_kr{}, i_f{}, i_st{}, i_to{}, i_p{}, i_naca{}, i_b{}, i_k1{}, i_sus{};
	//double i_bna{}, i_bca{}, i_bk{};
	double i_b_na{};
	double i_ach{}, fast_inact_ach{}, slow_inact_ach{}, g_ach_max{}, ach_conc{};
	double vol_cell{}, vol_sub{}, vol_i{}, vol_rel{}, vol_up{};
	double ca_sub{}, ca_rel{}, ca_up{}, p_rel{}, p_up{};
	double f_tc{}, f_tmc{}, f_tmm{}, f_cmi{}, f_cms{}, f_cq{};
	double f_csl{};
	double g_bna{}, g_bca{}, g_bk{};
	int l{}; //added for ach
public:
	av_node_2(int, int);
	av_node_2(int cell_type) {
		g_ach_max = 0.0198e-6;
		i_ach = 0;
		std::string filename;
		double* cell_parameters = new double[53];
		set_cell_type(cell_type);
		set_k_naca(SET_PARAMS(get_cm(), 2500.0e-12, 12187.5e-12));
		if (cell_type == 16) { //AN cell
			filename = "AnCell";
			filename.append(all_files_suffix);
		}
		else if (cell_type == 19) {
			filename = "NhCell";
			filename.append(all_files_suffix);
		}
		else {
			filename = "NCell_CONTROL";
			filename.append(all_files_suffix);
		}
		std::ifstream input_file{ filename };
		if (!input_file.good()) {
			std::cout << "Could not open file..." << std::endl;
			exit(1);
		}
		for (int j = 0; j < 53; ++j)
		{
			try {
				std::string new_value;
				getline(input_file, new_value);
				cell_parameters[j] = std::stod(new_value);
			}
			catch (...) {
				std::cout << j;
			}
		}
		input_file.close();
		//Set cell parameters
		set_g_na(cell_parameters[0]);
		set_g_ca(cell_parameters[1]);
		set_g_kr(cell_parameters[2]);
		set_g_to(cell_parameters[3]);
		set_g_k1(cell_parameters[4]);
		set_g_f(cell_parameters[5]);
		set_g_st(cell_parameters[6]);
		set_g_b(cell_parameters[7]);
		set_p_max(cell_parameters[8]);
		set_k_naca(cell_parameters[9]);
		set_i_stim(cell_parameters[10]);
		set_vm(cell_parameters[11]);
		set_vm_1(cell_parameters[12]);
		act_na = cell_parameters[13];
		fast_inact_na = cell_parameters[14];
		slow_inact_na = cell_parameters[15];
		act_l = cell_parameters[16];
		fast_inact_l = cell_parameters[17];
		slow_inact_l = cell_parameters[18];
		fast_act_kr = cell_parameters[19];
		slow_act_kr = cell_parameters[20];
		inact_kr = cell_parameters[21];
		act_f = cell_parameters[22];
		inact_st = cell_parameters[23];
		act_st = cell_parameters[24];
		act_to = cell_parameters[25];
		fast_inact_to = cell_parameters[26];
		slow_inact_to = cell_parameters[27];
		set_na_in(cell_parameters[28]);
		set_ca_in(cell_parameters[29]);
		set_k_in(cell_parameters[30]);
		ca_sub = cell_parameters[31];
		ca_rel = cell_parameters[32];
		ca_up = cell_parameters[33];
		p_rel = cell_parameters[34];//Cannot find data
		p_up = cell_parameters[35];//Cannot find fdata
		f_tc = cell_parameters[36];
		f_tmc = cell_parameters[37];
		f_tmm = cell_parameters[38];
		f_cmi = cell_parameters[39];
		f_cms = cell_parameters[40];
		f_cq = cell_parameters[41];
		f_csl = cell_parameters[42];
		set_cm(cell_parameters[43]);
		set_na_out(cell_parameters[44]);
		set_ca_out(cell_parameters[45]);
		set_k_out(cell_parameters[46]);
		rev_b = cell_parameters[47];
		rev_l = cell_parameters[48];
		rev_st = cell_parameters[49];
		g_bna = cell_parameters[50];
		g_bca = cell_parameters[51];
		g_bk = cell_parameters[52];
		rev_bna = -26.9E-03;
		set_g_b_na(3.2E-12);
		set_P_na(11.5E-16);
		vol_cell = SET_PARAMS(get_cm(), 2.19911e-12, 7.147123e-12);
		vol_sub = 0.01 * vol_cell;
		vol_i = 0.46 * vol_cell - vol_sub;
		vol_rel = 0.0012 * vol_cell;
		vol_up = 0.0116 * vol_cell;
		set_rev_na(55E-03);
		set_rev_k(-90E-03);
		set_rev_ca(134E-03);
		delete[] cell_parameters;
	}
	void print_currents(std::ofstream&,double,int);
	void export_cell(int);
	void calc_na(double, int);
	void initalise_avn(int);
	void calc_l(double, int);
	void calc_kr(double, int);
	void calc_to(double, int);
	void calc_f(double, int);
	void calc_st(double, int);
	void calc_b();
	void calc_p();
	void calc_naca();
	void calc_ach(double time_step, int solve_method, int l);
	void calc_ca_in(double, int);
	void calc_b_na();
	//void calc_vm(double time_step, int solve_method, double setVM, bool blocking_ibna, bool blocking_ical, double ical_block_multiplier);
	//Ach concentration set/ get (added 20/02/18)
	void set_vm_clamp(double voltage);
	void set_ach_conc(double insert_ach) {
		ach_conc = insert_ach;
	}
	double get_ach() {
		return ach_conc;
	}
	void set_ACh_level(int input_l) {
		l = input_l;
	}
	int get_ACh_level() {
		return l;
	}
	void calc_i_all(double time_step, int solve_method, int l)
	{ //l added for ACh present current alterations
		calc_na(time_step, solve_method);//ERROR
		calc_l(time_step, solve_method);
		calc_to(time_step, solve_method);
		calc_kr(time_step, solve_method);
		calc_st(time_step, solve_method);
		calc_f(time_step, solve_method);
		calc_b();
		calc_naca();
		calc_p();
		calc_ca_in(time_step, solve_method);
		calc_b_na();
		calc_ach(time_step, solve_method, l); //uncommented to	account for Ach K current
	}
	double get_total_ion(bool i_bna_zero) {
		//double total_ion =i_na + i_l + i_to + i_kr + i_st+ i_f+ i_b + i_k1 +i_naca + i_p+ i_ach;
		//REMOVED + i_bna + i_bca + i_bk
		//changed
		//For I_bNa set to zero
		//if (i_bna_zero) {
		//	total_ion -= i_b_na;
		//}
		/*if (get_cell_type() == 1){//Can use to adjust N cell frequency
		total_ion -= 0.5*i_b_na;
		}*/
		return (i_na + i_l + i_to + i_kr + i_st + i_f + i_b + i_k1 + i_naca + i_p + i_ach);
	}
	double calc_current_needed(double voltage, double time_step);

	void set_g_f(double g) {
		g_f = g;
	}
	double get_i_na() { return i_na; }
	double get_i_b_na() { return i_b_na; }
	double get_i_l() { return i_l; }
	double get_i_kr() { return i_kr; }
	double get_i_to() { return i_to; }
	double get_i_f() { return i_f; }
	double get_i_ach() { return i_ach; }
};

#endif