/*--------------------------------------------------------------------
-------- -
AV node cell action potential model
14 / 12 / 2007 Created by Shin INADA
11 / 04 / 2008 Modified by Shin INADA(add ACh sensitive current, added intracellular calciumdynamics)
07 / 11 / 2020 Modified by Noah PHIPPS (Optimisation of currents with respect to experimental data)
21 / 03 / 2021 Modified by Noah PHIPPS (Removing depreceated C style code, optimising functions, formatting, generally rewritten)
--------------------------------------------------------------------
------ */

#include <math.h>
#include "av_node_2.h"
//Atrioventricular node cell model
void av_node_2::initalise_avn(int cell_type) {
	g_ach_max = 0.0198e-6;
	i_ach = 0;
	std::string filename;
	double* cell_parameters = new double[53];
	set_cell_type(cell_type);
	set_k_naca(SET_PARAMS(get_cm(), 2500.0e-12, 12187.5e-12));
	if (cell_type == 16) { //AN cell
		filename = "AnCell";
		std::cout << "AN Cell...\n";
		filename.append(all_files_suffix);
	}
	else if (cell_type == 19) {
		filename = "NhCell";
		std::cout << "Nh Cell...\n";
		filename.append(all_files_suffix);
	}
	else {
		filename = "NCell_SKF";
		std::cout << "SKF N Cell...\n";
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
			std::cout << "Error, cannot read data when initialising AVN cell...";
			exit(1);
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
}

av_node_2::av_node_2(int cell_type, int version) {
	initalise_avn(cell_type);
	std::string filename{ import_file_prefix };
	filename.append(std::to_string(version));
	if (cell_type!=1) {
		filename.append(all_files_suffix);
	}
	else if(answer3==1){
		filename.append("_ach.txt");
		std::cout << "Importing ACh...\n";
		std::cout << filename;
	}
	else if (answer == 1) {
		filename.append("_skf.txt");
		std::cout << "Importing SKF...\n";
		std::cout << filename;
	}
	else {
		filename.append(all_files_suffix);
	}
	double* import_parameters = new double[71];
	std::ifstream input_file(filename);
	for (int i = 0; i < 71; i++)
	{
		try {
			std::string new_value;
			getline(input_file, new_value);
			import_parameters[i] = std::stod(new_value);
		}
		catch (...) {
			std::cout << "Error, cannot import AVN cell parameters...";
			exit(1);
		}
	}
	input_file.close();
	act_l = import_parameters[0];
	fast_inact_l = import_parameters[1];
	slow_inact_l = import_parameters[2];
	fast_act_kr = import_parameters[3];
	slow_act_kr = import_parameters[4];
	inact_kr = import_parameters[5];
	act_to = import_parameters[6];
	fast_inact_to = import_parameters[7];
	slow_inact_to = import_parameters[8];
	g_f = import_parameters[9];
	act_f = import_parameters[10];
	act_st = import_parameters[11];
	inact_st = import_parameters[12];
	rev_b = import_parameters[13];
	rev_l = import_parameters[14];
	rev_st = import_parameters[15];
	rev_bna = import_parameters[16];
	act_na = import_parameters[17];
	fast_inact_na = import_parameters[18];
	slow_inact_na = import_parameters[19];
	i_na = import_parameters[20];
	i_l = import_parameters[21];
	i_kr = import_parameters[22];
	i_f = import_parameters[23];
	i_st = import_parameters[24];
	i_to = import_parameters[25];
	i_p = import_parameters[26];
	i_naca = import_parameters[27];
	i_b = import_parameters[28];
	i_k1 = import_parameters[29];
	i_sus = import_parameters[30];
	i_b_na = import_parameters[31];
	i_ach = import_parameters[32];
	fast_inact_ach = import_parameters[33];
	slow_inact_ach= import_parameters[34];
	g_ach_max = import_parameters[35];
	ach_conc= import_parameters[36];
	vol_cell= import_parameters[37];
	vol_sub= import_parameters[38];
	vol_i = import_parameters[39];
	vol_rel = import_parameters[40];
	vol_up = import_parameters[41];
	ca_sub = import_parameters[42];
	ca_rel = import_parameters[43];
	ca_up = import_parameters[44];
	p_rel= import_parameters[45];
	p_up = import_parameters[46];
	f_tc = import_parameters[47];
	f_tmc = import_parameters[48];
	f_tmm = import_parameters[49];
	f_cmi= import_parameters[50];
	f_cms= import_parameters[51];
	f_cq= import_parameters[52];
	f_csl= import_parameters[53];
	g_bna= import_parameters[54];
	g_bca= import_parameters[55];
	g_bk= import_parameters[56];
	//l= static_cast<int>(import_parameters[57]);
	//Now the cell base parameters
	set_vm(import_parameters[58]);
	set_vm_1(import_parameters[59]);
	set_i_stim(import_parameters[60]);
	set_ca_out(import_parameters[61]);
	set_na_out(import_parameters[62]);
	set_k_out(import_parameters[63]);
	set_na_in(import_parameters[64]);
	set_ca_in(import_parameters[65]);
	set_k_in(import_parameters[66]);
	set_rev_na(import_parameters[67]);
	set_rev_k(import_parameters[68]);
	set_rev_ca(import_parameters[69]);
	set_coupling_conductance(import_parameters[70]);
}

void av_node_2::export_cell(int version) {
	std::string filename{ "avn_export_" };
	filename.append(std::to_string(version));
	filename.append(all_files_suffix);
	std::ofstream output_file{ filename };
	double* export_parameters = new double[71];
	export_parameters[0] = act_l;
	export_parameters[1] = fast_inact_l;
	export_parameters[2] = slow_inact_l;
	export_parameters[3] = fast_act_kr;
	export_parameters[4] = slow_act_kr;
	export_parameters[5] = inact_kr;
	export_parameters[6] = act_to;
	export_parameters[7] = fast_inact_to;
	export_parameters[8] = slow_inact_to;
	export_parameters[9] = g_f;
	export_parameters[10] = act_f;
	export_parameters[11] = act_st;
	export_parameters[12] = inact_st;
	export_parameters[13] = rev_b;
	export_parameters[14] = rev_l;
	export_parameters[15] = rev_st;
	export_parameters[16] = rev_bna;
	export_parameters[17] = act_na;
	export_parameters[18] = fast_inact_na;
	export_parameters[19] = slow_inact_na;
	export_parameters[20] = i_na;
	export_parameters[21] = i_l;
	export_parameters[22] = i_kr;
	export_parameters[23] = i_f;
	export_parameters[24] = i_st;
	export_parameters[25] = i_to;
	export_parameters[26] = i_p;
	export_parameters[27] = i_naca;
	export_parameters[28] = i_b;
	export_parameters[29] = i_k1;
	export_parameters[30] = i_sus;
	export_parameters[31] = i_b_na;
	export_parameters[32] = i_ach;
	export_parameters[33] = fast_inact_ach;
	export_parameters[34] = slow_inact_ach;
	export_parameters[35] = g_ach_max;
	export_parameters[36] = ach_conc;
	export_parameters[37] = vol_cell;
	export_parameters[38] = vol_sub;
	export_parameters[39] = vol_i;
	export_parameters[40] = vol_rel;
	export_parameters[41] = vol_up;
	export_parameters[42] = ca_sub;
	export_parameters[43] = ca_rel;
	export_parameters[44] = ca_up;
	export_parameters[45] = p_rel;
	export_parameters[46] = p_up;
	export_parameters[47] = f_tc;
	export_parameters[48] = f_tmc;
	export_parameters[49] = f_tmm;
	export_parameters[50] = f_cmi;
	export_parameters[51] = f_cms;
	export_parameters[52] = f_cq;
	export_parameters[53] = f_csl;
	export_parameters[54] = g_bna;
	export_parameters[55] = g_bca;
	export_parameters[56] = g_bk;
	export_parameters[57] = l;
	//Now the cell base parameters
	export_parameters[58] = get_vm();
	export_parameters[59] = get_vm_1();
	export_parameters[60] = get_i_stim();
	export_parameters[61] = get_ca_out();
	export_parameters[62] = get_na_out();
	export_parameters[63] = get_k_out();
	export_parameters[64] = get_na_in();
	export_parameters[65] = get_ca_in();
	export_parameters[66] = get_k_in();
	export_parameters[67] = get_rev_na();
	export_parameters[68] = get_rev_k();
	export_parameters[69] = get_rev_ca();
	export_parameters[70] = get_coupling_conductance();
	for (int i{}; i < 71; i++) {
		output_file<< export_parameters[i];
		if (i != 70) {
			output_file << std::endl;
		}
	}
	output_file.close();
}

void av_node_2::calc_na(double time_step, int solve_method) {
	//Definition of local variables
	double steady_state, time_constant, diff_value;
	double alpha, beta;
	//Activation value
	if (fabs(get_vm() + 44.4e-3) > NEGLIGIBLE_SMALL) {
		alpha = -460.000 * (get_vm() * 1.0e+3 + 44.4) / (exp((get_vm() * 1.0e+3 + 44.4) / -12.673) - 1.0);
	}
	else {
		alpha = -460.000 * -12.673 / exp((get_vm() * 1.0e+3 + 44.4) / -12.673);
	}
	beta = 18400.000 * exp((get_vm() * 1.0e+3 + 44.4) / -12.673);
	diff_value = alpha * (1.0 - act_na) - beta * act_na;
	act_na = solve_diff_eqn(act_na, diff_value, time_step, solve_method);
	//Fast inactivation value
	alpha = 44.900 * exp((get_vm() * 1.0e+3 + 66.9) / -5.570);
	beta = 1491.000 / (1.0 + 323.300 * exp((get_vm() * 1.0e+3 + 94.6) / -12.900));
	time_constant = 0.03000 / (1.0 + exp((get_vm() * 1.0e+3 + 40.00) / 6.000)) + 0.00035;
	steady_state = alpha / (alpha + beta);
	diff_value = (steady_state - fast_inact_na) / time_constant;
	fast_inact_na = solve_diff_eqn(fast_inact_na, diff_value, time_step, solve_method);
	//Slow inactivation value
	time_constant = 0.12000 / (1.0 + exp((get_vm() * 1.0e+3 + 60.00) / 2.000)) + 0.00295;
	diff_value = (steady_state - slow_inact_na) / time_constant;
	slow_inact_na = solve_diff_eqn(slow_inact_na, diff_value, time_step, solve_method);
	//Calculate sodium current
	if (fabs(get_vm()) > NEGLIGIBLE_SMALL) {
		i_na =
			get_g_na() * pow(act_na, 3.0)
			* (0.635 * fast_inact_na + 0.365 * slow_inact_na)
			* get_na_out() * get_vm() * pow(F, 2.0) / (R * T)
			* (exp((get_vm() - get_rev_na()) * (F / (R * T))) - 1.0)
			/ (exp(get_vm() * F / (R * T)) - 1.0);
	}
	else {
		i_na =
			get_g_na() * pow(act_na, 3.0)
			* (0.635 * fast_inact_na + 0.365 * slow_inact_na)
			* get_na_out() * pow(F, 2.0) / (R * T)
			* (exp((get_vm() - get_rev_na()) * F / (R * T))
			+ get_vm() * F / (R * T)
			* exp((get_vm() - get_rev_na()) * F / (R * T)) - 1.0)
			/ (F / (R * T) * exp(get_vm() * F / (R * T)));
	}
}

void av_node_2::calc_b_na() {
	double P_na = 11.5E-16;//Changed from 7.308 to 5.78 11.5
	double vm = get_vm();
	i_b_na =
		get_P_na() * vm * ((pow(F, 2)) / (R * T)) * ((get_na_in() -
			((get_na_out()) * exp(-(F * vm) / (R * T)))) / (1 - (exp(-(vm * F) /
				(R * T)))));
}
void av_node_2::calc_l(double time_step, int solve_method) {
	//Definition of variables
	double alpha, beta;
	double steady_state, time_constant, diff_value;
	double act_shift, inact_shift;
	double slope_factor_act; //(Added 26/10/2008)
	double slope_factor_inact = 0;
	if (get_cell_type() == 6 || get_cell_type() == 16) {
		act_shift = 0;
		inact_shift = -3.0;
		slope_factor_act = -7.5;
	}
	else if (get_cell_type() == 9 || get_cell_type() == 19) {
		act_shift = 2.0;//Affects APD SET BEFORE ICAL BLOCK FIXING: 2
		inact_shift = -15;//-5 SET BEFORE ICAL BLOCK FIXING: -15
		slope_factor_act = -8.85;//-6.61, set? SET BEFORE ICAL BLOCK FIXING: -8.85
	}
	else {
		act_shift = -5;//-7
		inact_shift = -4.8;//-5
		slope_factor_act = -5.2;//FREQ FROM -7 TO -5
		slope_factor_inact = 2.8;//Changed from 2, 2.3
		//slope_factor_act = -6.61;
	}
	//Activation value
	alpha = (-26.12 * (get_vm() * 1.0e+3 + 35.0)) / (exp((get_vm() * 1.0e+3 + 35.0) / -2.5) - 1.0) + (-78.11 * get_vm() * 1.0e+3) / (exp(-0.208 * get_vm() * 1.0e+3) - 1.0);//CHECKED
	beta = (10.52 * (get_vm() * 1.0e+3 - 5.0)) / (exp(0.4 * (get_vm() * 1.0e+3 - 5.0)) - 1.0);//CHECKED
	time_constant = 1.0 / (alpha + beta);//CHECKED
	//Changed (26/10/2008)
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 - (-3.2 + act_shift)) / slope_factor_act));
	diff_value = (steady_state - act_l) / time_constant;
	act_l = solve_diff_eqn(act_l, diff_value, time_step, solve_method);
	//Fast inactivation value
	time_constant = 0.010 + 0.1539 * exp(-pow(get_vm() * 1.0e+3 + 40.0, 2.0) / 185.67);
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 - (-24.0 + inact_shift)) / (6.31 + slope_factor_inact)));//Added slope_factor_inact_shift 
	diff_value = (steady_state - fast_inact_l) / time_constant;
	fast_inact_l = solve_diff_eqn(fast_inact_l, diff_value, time_step, solve_method);
	//Slow inactivation value
	time_constant = 0.060 + 0.48076 * 2.25 * exp(-pow(get_vm() * 1.0e+3 - (-40.0), 2.0) / 138.04);
	diff_value = (steady_state - slow_inact_l) / time_constant;
	slow_inact_l = solve_diff_eqn(slow_inact_l, diff_value, time_step, solve_method);
	//Calculate current
	i_l = get_g_ca() * act_l * (0.675 * fast_inact_l + 0.325 * slow_inact_l) * (get_vm() - rev_l);
	//Effect of ACh (added 11/04/2008)
	double ical_mult = 1 - (get_i_ach() / (0.9e-9 + get_i_ach()));
	i_l *= ical_mult;
	//Effect of I_Ca,L rescue
	//i_l *= get_i_l_rescue(); TODO
}
void av_node_2::calc_kr(double time_step, int solve_method) {
	//Definition of variables
	double alpha, beta;
	double steady_state, time_constant, diff_value;
	// parameters to fit experimental control & skf data to si (added 11 / 11 / 17)
	//TODO
	//Should this be changed to be the same as AVN initial code model?
	double act_shift = 2, inact_shift = 20, slope_shift = 0, slope_shift_inact = 0;//Maybe inact shift to adjust apd
	//Fast activaton value
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 + 10.22 + act_shift) / (-8.50 + slope_shift)));
	time_constant = 1.0 / (17.0 * exp(0.0398 * get_vm() * 1.0e+3) + 0.211 * exp(-0.0510 * get_vm() * 1.0e+3));
	diff_value = (steady_state - fast_act_kr) / time_constant;
	fast_act_kr = solve_diff_eqn(fast_act_kr, diff_value, time_step, solve_method);
	//Slow activation value
	time_constant = 0.33581 + 0.90673 * exp(-pow(get_vm() * 1.0e+3 + 10.0, 2.0) / 988.05);
	diff_value = (steady_state - slow_act_kr) / time_constant;
	slow_act_kr = solve_diff_eqn(slow_act_kr, diff_value, time_step, solve_method);
	//Inactivation value
	alpha = 92.01 * exp(-0.0183 * get_vm() * 1.0e+3);
	beta = 603.6 * exp(0.00942 * get_vm() * 1.0e+3);
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 + 4.90 + inact_shift) / (15.14 + slope_shift_inact)));
	steady_state *= (1.0 - 0.3 * exp(-pow(get_vm() * 1.0e+3, 2.0) / 500.0));
	time_constant = 1.0 / (alpha + beta);
	diff_value = (steady_state - inact_kr) / time_constant;
	inact_kr = solve_diff_eqn(inact_kr, diff_value, time_step, solve_method);
	//Calculate potassium ion current
	i_kr = get_g_kr() * (0.90 * fast_act_kr + 0.10 * slow_act_kr) * inact_kr * (get_vm() - get_rev_k());
}
void av_node_2::calc_to(double time_step, int solve_method) {
	//Definition of local variables
	double steady_state, time_constant, diff_value;
	double fraction_inactivation_fast;
	double act_shift = 0, inact_shift = 0, slope_shift = 0, slope_shift_inact = 0;
	//Activation value
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 - 7.44 + act_shift) / (-16.4 + slope_shift)));
	time_constant = 0.596e-3 + 3.118e-3 / (1.037 * exp(0.09 * (get_vm() * 1.0e+3 + 30.61)) + 0.396 * exp(-0.12 * (get_vm() * 1.0e+3 + 23.84)));
	diff_value = (steady_state - act_to) / time_constant;
	act_to = solve_diff_eqn(act_to, diff_value, time_step, solve_method);
	//Fast inactivation value
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 + 33.8 + inact_shift) / (6.12 + slope_shift_inact)));
	time_constant = 12.66e-3 + 4.72716 / (1.0 + exp((get_vm() * 1.0e+3 + 154.5) / 23.96));
	diff_value = (steady_state - fast_inact_to) / time_constant;
	fast_inact_to = solve_diff_eqn(fast_inact_to, diff_value, time_step, solve_method);
	//Slow inactivation value
	time_constant = 0.100 + 4.000 * exp(-pow(get_vm() * 1.0e+3 + 65.0, 2.0) / 500.0);
	diff_value = (steady_state - slow_inact_to) / time_constant;
	slow_inact_to = solve_diff_eqn(slow_inact_to, diff_value, time_step, solve_method);
	//Fraction of inactivation
	fraction_inactivation_fast = 0.45;
	//Calculate current
	i_to = get_g_to() * act_to * (fraction_inactivation_fast * fast_inact_to + (1.0 - fraction_inactivation_fast) * slow_inact_to) * (get_vm() - get_rev_k());
}
void av_node_2::calc_f(double time_step, int solve_method) {
	//Definition of local variables
	double steady_state, time_constant, diff_value;
	double act_shift = 0, slope_shift = 0;
	//Effect of acetylcholine (11/04/2008)
	/*act_shift =
	-7.2 * pow(get_ach(), 0.69)
	/ (pow(1.26e-8, 0.69) + pow(get_ach(), 0.69));*/
	//CHANGED
	//Activation value
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 - (-83.19) - act_shift) / 13.56 + slope_shift));//CHECKED
	time_constant = 0.250 + 2.000 * exp(-pow(get_vm() * 1.0e+3 - (-70.00), 2.0) / 500.0);//CHECKED
	diff_value = (steady_state - act_f) / time_constant;//CHECKED
	act_f = solve_diff_eqn(act_f, diff_value, time_step, solve_method);
	i_f = g_f * act_f * (get_vm() - (-0.030));//CHECKED
}
void av_node_2::calc_st(double time_step, int solve_method) {
	//Definition of local variables
	double alpha, beta;
	double steady_state, time_constant, diff_value;
	double act_shift = .3, slope_shift = .2;//(0,0 originally) (0.3, ?) works, .3 total is good
	//Activation value
	steady_state = 1.0 / (1.0 + exp((get_vm() * 1.0e+3 - (-49.10 + act_shift)) / (-8.98 + slope_shift)));//CHECKED
	alpha = 1.0 / (0.15 * exp(-get_vm() * 1.0e+3 / 11.0) + 0.20 * exp(-get_vm() * 1.0e+3 / 700.0));//CHECKED
	beta = 1.0 / (16.0 * exp(get_vm() * 1.0e+3 / 8.0) + 15.0 * exp(get_vm() * 1.0e+3 / 50.0));//CHECKED
	time_constant = 1.0e-3 / (alpha + beta);//CHECKED
	diff_value = (steady_state - act_st) / time_constant;//CHECKED
	act_st = solve_diff_eqn(act_st, diff_value, time_step, solve_method);
	//Inactivation value
	alpha = 0.1504 / (3100.0 * exp(get_vm() * 1.0e+3 / 13.0) + 700.0 * exp(get_vm() * 1.0e+3 / 70.0));//CHECKED
	beta = 0.1504 / (95.0 * exp(-get_vm() * 1.0e+3 / 10.0) + 50.0 * exp(-get_vm() * 1.0e+3 / 700.0)) + 0.000229 / (1.0 + exp(-get_vm() * 1.0e+3 / 5.0));//CHECKED
	steady_state = alpha / (alpha + beta);//CHECKED
	time_constant = 1.0e-3 / (alpha + beta);//CHECKED
	diff_value = (steady_state - inact_st) / time_constant;//CHECKED
	inact_st = solve_diff_eqn(inact_st, diff_value, time_step, solve_method);
	i_st = get_g_st() * act_st * inact_st * (get_vm() - rev_st);//CHECKED
}
void av_node_2::calc_b() {
	//Definition of local variable
	double g_k1_;
	/*i_bna = g_bna * (get_vm() - get_rev_na());
	i_bca = g_bca * (get_vm() - get_rev_ca());
	i_bk = g_bk * (get_vm() - get_rev_k());*/
	//i_bna = i_bca = i_bk = 0.0;//CHANGED
	i_b = get_g_b() * (get_vm() - rev_b);
	g_k1_ = get_g_k1() * (0.5 + 0.5 / (1.0 + exp((get_vm() * 1.0e+3 - (-30.0)) / 5.0)));
	i_k1 = g_k1_ * pow(get_k_out() / (get_k_out() + 0.590e-3), 3.0) * (get_vm() - (-0.0819)) / (1.0 + exp(1.393 * (get_vm() - (-0.0819) + 0.0036) * F / (R * T)));
}
void av_node_2::calc_p() {
	i_p =
		get_p_max() * pow(get_na_in() * 1.0e+3 / (5.64 + get_na_in() *
			1.0e+3), 3.0)
		* pow(get_k_out() * 1.0e+3 / (0.621 + get_k_out() *
			1.0e+3), 2.0)
		* 1.6 / (1.5 + exp(-(get_vm() * 1.0e+3 + 60.0) / 40.0));
}
void av_node_2::calc_naca() {
	//Local variables
	double d_i, d_o, x1, x2, x3, x4;
	double k12, k14, k21, k23, k32, k34, k41, k43;
	d_i = 1.0 + (ca_sub / 0.0207e-3) * (1.0 + exp(-0.1369 * get_vm() * F / (R * T)) + get_na_in() / 26.44e-3) + (get_na_in() / 395.3e-3) * (1.0 + (get_na_in() / 2.289e-3) * (1.0 + get_na_in() / 26.44e-3));
	d_o = 1.0 + (get_ca_out() / 3.663e-3) * (1.0 + exp(0.0 * get_vm() * F / (R * T))) + (get_na_out() / 1628.0e-3) * (1.0 + (get_na_out() / 561.4e-3) * (1.0 + get_na_out() / 4.663e-3));
	k43 = get_na_in() / (26.44e-3 + get_na_in());
	k12 = (ca_sub / 0.0207e-3) * exp(-0.1369 * get_vm() * F / (R * T)) / d_i;
	k14 = (get_na_in() / 395.3e-3) * (get_na_in() / 2.289e-3) * (1.0 + get_na_in() / 26.44e-3) * exp(0.4315 * get_vm() * F / (2.0 * R * T)) / d_i;
	k41 = exp(-0.4315 * get_vm() * F / (2.0 * R * T));
	k34 = get_na_out() / (4.663e-3 + get_na_out());
	k21 = (get_ca_out() / 3.663e-3) * exp(0.0 * get_vm() * F / (R * T)) / d_o;
	k23 = (get_na_out() / 1628.0e-3) * (get_na_out() / 561.4e-3) * (1.0 + get_na_out() / 4.663e-3) * exp(-0.4315 * get_vm() * F / (2.0 * R * T)) / d_o;
	k32 = exp(0.4315 * get_vm() * F / (2.0 * R * T));
	x1 = k34 * k41 * (k23 + k21) + k21 * k32 * (k43 + k41);
	x2 = k43 * k32 * (k14 + k12) + k41 * k12 * (k34 + k32);
	x3 = k43 * k14 * (k23 + k21) + k12 * k23 * (k43 + k41);
	x4 = k34 * k23 * (k14 + k12) + k21 * k14 * (k34 + k32);
	//Ionic current
	i_naca = get_k_naca() * (k21 * x2 - k12 * x1) / (x1 + x2 + x3 + x4);
}
//Acetylcholine sensitive current (added 11/04/2008) //Changed to AVN IC model version
void av_node_2::calc_ach(double time_step, int solve_method, int l)
{
	if (get_cell_type() != 1) {
		l = 0;
	}
	double alpha, beta, diff_value, g_ach;
	double k_ach = 3.5e-7;
	double fastInactShift{ 0 }, fastSlopeShift{ 0 }, slowInactShift{ 0 }, slowSlopeShift{ 0 }, scaling_I{ 0 }, shift_I{ 0 };
	//double slopeinput = -15 + l*10;	
	if (l == 0) {
	set_ach_conc(0);
	}
	else if (l == 1) {
		set_ach_conc(pow(10, -6));
		fastInactShift = 10;
		fastSlopeShift = 0;
		slowInactShift = 30;
		slowSlopeShift = 0;
		scaling_I = 5.5; // orig: 6.15 1: 7.29 2: 6.7	5.5
		shift_I = -12 * pow(10, -11);
	}
	else if (l == 2) {
		set_ach_conc(pow(10, -7));
		fastInactShift = 10;
		fastSlopeShift = 10;
		slowInactShift = -30;
		slowSlopeShift = 15;
		scaling_I = 15;//16
		shift_I = -7 * pow(10, -11);//8.96
	}
	else if (l == 3) {
		set_ach_conc(0.5 * pow(10, -7));
		fastInactShift = 30;
		fastSlopeShift = 10;
		slowInactShift = -30;
		slowSlopeShift = 15;
		scaling_I = 20;//28
		shift_I = -3.21 * pow(10, -11);//2.61
	}
	else if (l == 4) {
		set_ach_conc(0.3 * pow(10, -7));
		fastInactShift = 20;
		fastSlopeShift = 0;
		slowInactShift = -50;
		slowSlopeShift = -5;
		scaling_I = 11.326; //orig: 12.3 1: 11.326	
		shift_I = -1.35 * pow(10, -11);
	}
	else if (l == 5) {
		set_ach_conc(pow(10, -8));
		fastInactShift = 20;
		fastSlopeShift = 10;
		slowInactShift = -10;
		slowSlopeShift = 20;
		scaling_I = 1; //orig: 16 1: 0	
		shift_I = 0.2 * pow(10, -11);
	}
	alpha = 73.1;
	beta = 120 / (1.0 + exp(-(get_vm() * 1.0e+3 + 50.0 + fastInactShift) / (15.0 + fastSlopeShift)));
	diff_value = alpha * (1.0 - fast_inact_ach) - beta * fast_inact_ach;//dj/dt	
	fast_inact_ach = solve_diff_eqn(fast_inact_ach, diff_value, time_step, solve_method);
	alpha = 3.7;
	beta = 5.82 / (1.0 + exp(-(get_vm() * 1.0e+3 + 50.0 + slowInactShift) / (15.0 + slowSlopeShift)));
	diff_value = alpha * (1.0 - slow_inact_ach) - beta * slow_inact_ach;
	slow_inact_ach = solve_diff_eqn(slow_inact_ach, diff_value, time_step, solve_method);
	//Calculate conductance	
	g_ach = g_ach_max * fast_inact_ach * slow_inact_ach * pow(get_ach(), 1.5) / (pow(k_ach, 1.5) + pow(get_ach(), 1.5));
	//Calculate current	
	i_ach = shift_I + scaling_I * g_ach * (get_k_out() / (10.0e-3 + get_k_out())) * ((get_vm() - get_rev_k()) / (1.0 + exp((get_vm() - get_rev_k() - 140.0e-3) * F / (2.5 * R * T))));
}

void av_node_2::calc_ca_in(double time_step, int solve_method) {
	//Local variables
	double diff_value, result;
	double j_ca, j_rel, j_up, j_tr;
	double diff_f_tc, diff_f_tmc, diff_f_tmm;
	double diff_f_cmi, diff_f_cms, diff_f_cq;
	double diff_f_csl;
	//Ca2+ diffusion flux
	j_ca = (ca_sub - get_ca_in()) / 0.04e-3;
	//Ca2+ handling by the SR
	j_rel = p_rel * (ca_rel - ca_sub) / (1.0 + pow(0.0012e-3 / ca_sub, 2.0));
	j_up = 3.0 * 0.005 / (1.0 + 0.0006e-3 / get_ca_in());
	j_up = 1.0 * 0.005 / (1.0 + 0.0006e-3 / get_ca_in());
	j_tr = (ca_up - ca_rel) / 60.0e-3;
	//Ca2+ buffering
	diff_f_tc = 88.8e+6 * get_ca_in() * (1.0 - f_tc) - 0.446e+3 * f_tc;
	diff_f_tmc = 227.7e+6 * get_ca_in() * (1.0 - f_tmc - f_tmm) - 0.00751e+3 * f_tmc;
	diff_f_tmm = 2.277e+6 * 2.5e-3 * (1.0 - f_tmc - f_tmm) - 0.751e+3 * f_tmm;
	diff_f_cmi = 227.7e+6 * get_ca_in() * (1.0 - f_cmi) - 0.542e+3 * f_cmi;
	diff_f_cms = 227.7e+6 * ca_sub * (1.0 - f_cms) - 0.542e+3 * f_cms;
	diff_f_cq = 0.534e+6 * ca_rel * (1.0 - f_cq) - 0.445e+3 * f_cq;
	diff_f_csl = 115.0 * 1000.0 * ca_sub * (1.0 - f_csl) - 1000.0 * f_csl;
	diff_f_csl *= 0.001;
	//diff_f_csl = 0.0;
	f_tc = solve_diff_eqn(f_tc, diff_f_tc, time_step, solve_method);
	f_tmc = solve_diff_eqn(f_tmc, diff_f_tmc, time_step, solve_method);
	f_tmm = solve_diff_eqn(f_tmm, diff_f_tmm, time_step, solve_method);
	f_cmi = solve_diff_eqn(f_cmi, diff_f_cmi, time_step, solve_method);
	f_cms = solve_diff_eqn(f_cms, diff_f_cms, time_step, solve_method);
	f_cq = solve_diff_eqn(f_cq, diff_f_cq, time_step, solve_method);
	f_csl = solve_diff_eqn(f_csl, diff_f_csl, time_step, solve_method);
	//Myoplasmic Ca2+ concentrations
	diff_value = (j_ca * vol_sub - j_up * vol_up) / vol_i - (0.045e-3 * diff_f_cmi + 0.031e-3 * diff_f_tc + 0.062e-3 * diff_f_tmc);
	result = solve_diff_eqn(get_ca_in(), diff_value, time_step, solve_method);
	set_ca_in(result);
	//Subspace Ca2+ concentration
	diff_value = (-(i_l - 2.0 * i_naca) / (2.0 * F) + j_rel * vol_rel) / vol_sub - j_ca - 0.045e-3 * diff_f_cms - (0.031 / 1.2) * diff_f_csl;
	ca_sub = solve_diff_eqn(ca_sub, diff_value, time_step, solve_method);
	//Ca2+ concentration in junctonal SR
	diff_value = j_tr - j_rel - 10.0e-3 * diff_f_cq;
	ca_rel = solve_diff_eqn(ca_rel, diff_value, time_step, solve_method);
	//Ca2+ concentration in network SR
	diff_value = j_up - j_tr * vol_rel / vol_up;
	ca_up = solve_diff_eqn(ca_up, diff_value, time_step, solve_method);
}

// Voltage clamping, set voltage to const.
void av_node_2::set_vm_clamp(double voltage) {
	set_vm(voltage);
}

double av_node_2::calc_current_needed(double voltage, double time_step) {
	double vm = get_vm();
	double diff_vm;
	double current_needed;
	diff_vm = (voltage - vm) / time_step;
	current_needed = -diff_vm * (get_cm());
	return current_needed;
}
void av_node_2::print_currents(std::ofstream &output_file,double time, int cell_type) {
	output_file << cell_type << "\t" << time << "\t" << i_na << "\t" << i_l << "\t" << i_kr << "\t" << i_f << "\t" << i_st << "\t" << i_to << "\t" << i_p << "\t" << i_naca << "\t" << i_b << "\t" << i_k1 << "\t" << i_sus << std::endl;
}
