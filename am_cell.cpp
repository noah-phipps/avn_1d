/*--------------------------------------------------------------------
-------- -
AM Cell Action Potential Model
21 / 03 / 2021 Modified by Noah PHIPPS and Gemma LAMB (Removing depreceated C style code, optimising functions, formatting, generally rewritten)
22 / 03 / 2021 Rewritten by Noah PHIPPS and Gemma LAMB (Created functions for currents)
--------------------------------------------------------------------
------ */
#include "am_cell.h"
#include<string>
#include<fstream>
#include<vector>
#include <iostream>
am_cell::am_cell(int version) {

	initialise();

	std::string filename{ import_file_prefix };
	filename.append(std::to_string(version));
	filename.append(all_files_suffix);
	double* import_parameters = new double[45];
	std::ifstream input_file{ filename };
	for (int i = 0; i < 45; i++)
	{
		try {
			std::string new_value;
			getline(input_file, new_value);
			import_parameters[i] = std::stod(new_value);
		}
		catch (...) {
			std::cout << "Error, cannot read data when importing am_cell parameters...";
			exit(1);
		}
	}
	input_file.close();
	n = import_parameters[0];
	r1 = import_parameters[1];
	s1 = import_parameters[2];
	s2 = import_parameters[3];
	s3 = import_parameters[4];
	s3 = import_parameters[5];
	m = import_parameters[6];
	h1 = import_parameters[7];
	h2 = import_parameters[8];
	dL = import_parameters[9];
	fL = import_parameters[10];
	dT = import_parameters[11];
	fT = import_parameters[12];
	Pa = import_parameters[13];
	Pi = import_parameters[14];
	EK = import_parameters[15];
	ENa = import_parameters[16];
	ECa = import_parameters[17];
	ECl = import_parameters[18];
	EbCl = import_parameters[19];
	INa = import_parameters[20];
	IK = import_parameters[21];
	Ik1 = import_parameters[22];
	Ito = import_parameters[23];
	INaCa = import_parameters[24];
	Ip = import_parameters[25];
	Ib = import_parameters[26];
	ICap = import_parameters[27];
	ICaL = import_parameters[28];
	ICaT = import_parameters[29];
	Isus = import_parameters[30];
	i_b_na = import_parameters[31];
	//Now the cell base parameters
	set_vm(import_parameters[32]);
	set_vm_1(import_parameters[33]);
	set_i_stim(import_parameters[34]);
	set_ca_out(import_parameters[35]);
	set_na_out(import_parameters[36]);
	set_k_out(import_parameters[37]);
	set_na_in(import_parameters[38]);
	set_ca_in(import_parameters[39]);
	set_k_in(import_parameters[40]);
	set_rev_na(import_parameters[41]);
	set_rev_k(import_parameters[42]);
	set_rev_ca(import_parameters[43]);
	set_coupling_conductance(import_parameters[44]);

}

void am_cell::export_cell(int version) {
	std::string filename{ "am_export_" };
	filename.append(std::to_string(version));
	filename.append(all_files_suffix);
	std::ofstream output_file{ filename };
	double* export_parameters = new double[45];
	export_parameters[0] = n;
	export_parameters[1] = r1;
	export_parameters[2] = s1;
	export_parameters[3] = s2;
	export_parameters[4] = s3;
	export_parameters[5] = s3;
	export_parameters[6] = m;
	export_parameters[7] = h1;
	export_parameters[8] = h2;
	export_parameters[9] = dL;
	export_parameters[10] = fL;
	export_parameters[11] = dT;
	export_parameters[12] = fT;
	export_parameters[13] = Pa;
	export_parameters[14] = Pi;
	export_parameters[15] = EK;
	export_parameters[16] = ENa;
	export_parameters[17] = ECa;
	export_parameters[18] = ECl;
	export_parameters[19] = EbCl;
	export_parameters[20] = INa;
	export_parameters[21] = IK;
	export_parameters[22] = Ik1;
	export_parameters[23] = Ito;
	export_parameters[24] = INaCa;
	export_parameters[25] = Ip;
	export_parameters[26] = Ib;
	export_parameters[27] = ICap;
	export_parameters[28] = ICaL;
	export_parameters[29] = ICaT;
	export_parameters[30] = Isus;
	export_parameters[31] = i_b_na;
	//Now the cell base parameters
	export_parameters[32] = get_vm();
	export_parameters[33] = get_vm_1();
	export_parameters[34] = get_i_stim();
	export_parameters[35] = get_ca_out();
	export_parameters[36] = get_na_out();
	export_parameters[37] = get_k_out();
	export_parameters[38] = get_na_in();
	export_parameters[39] = get_ca_in();
	export_parameters[40] = get_k_in();
	export_parameters[41] = get_rev_na();
	export_parameters[42] = get_rev_k();
	export_parameters[43] = get_rev_ca();
	export_parameters[44] = get_coupling_conductance();

	for (int i{}; i < 45; i++) {
		output_file << export_parameters[i];
		if (i != 44) {
			output_file << std::endl;
		}
	}
	output_file.close();
}

void am_cell::print_currents(std::ofstream& output_file, double time, int cell_type) {
	output_file << cell_type << "\t" << time << "\t" << INa << "\t" << IK << "\t" << Ik1 << "\t" << Ito << "\t" << INaCa << "\t" << Ip << "\t" << Ib << "\t" << ICap << "\t" << ICaL << "\t" << ICaT << "\t" << Isus << std::endl;
}

double am_cell::get_total_ion(bool i_bna_zero) {
	//double I = ((INa + IK + Ik1 + Ito + INaCa + Ip + Ib + ICap + ICaL + ICaT + Isus));
	//if (i_bna_zero) {
	//	I -= i_b_na;
	//}
	return (INa + IK + Ik1 + Ito + INaCa + Ip + Ib + ICap + ICaL + ICaT);//Removed Isus
}

void am_cell::calc_i_all(double time_step, int solve_method, int l) {
	calc_INa(time_step, solve_method);
	calc_IK(time_step, solve_method);
	calc_Ik1(time_step, solve_method);
	calc_Ito(time_step, solve_method);
	calc_INaCa(time_step, solve_method);
	calc_Ip(time_step, solve_method);
	calc_Ib(time_step, solve_method);
	calc_ICap(time_step, solve_method);
	calc_ICaL(time_step, solve_method);
	calc_ICaT(time_step, solve_method);
	calc_Isus(time_step, solve_method);
	calc_i_b_na(time_step, solve_method);
}

void am_cell::calc_INa(double time_step, int solve_method) {
	double alpha_m, beta_m, m_inf, tau_m;
	double alpha_h, beta_h, h_inf, tau_h1, tau_h2;
	double vm_mv = get_vm() * 1000;

	//INa
	alpha_m = -460 * (vm_mv + 44.4) / (exp(-(vm_mv + 44.4) / 12.673) - 1);
	beta_m = 18400.0 * exp(-(vm_mv + 44.4) / 12.673);
	m_inf = alpha_m / (alpha_m + beta_m);//Unsure about this
	tau_m = 1000 / (alpha_m + beta_m);//Unsure about this
	m += HT * (m_inf - m) / tau_m;//Unsure about this

	alpha_h = 44.9 * exp(-(vm_mv + 66.9) / 5.57);
	beta_h = 1491.0 / (1 + 323.3 * exp(-(vm_mv + 94.6) / 12.9));
	tau_h1 = 1000 * (0.03 / (1 + exp((vm_mv + 40) / 6.0)) + 0.00035);
	tau_h2 = 1000 * (0.12 / (1 + exp((vm_mv + 60) / 2.0)) + 0.00295);
	h_inf = alpha_h / (alpha_h + beta_h);
	h1 += HT * (h_inf - h1) / tau_h1;
	h2 += HT * (h_inf - h2) / tau_h2;
	INa = get_P_na() * NaIono * F * F/(R*T) * pow(m, 3) * (0.635 * h1 + 0.365 * h2) * vm_mv * (exp((vm_mv - ENa)*(F/(R*T))) - 1) / (exp(vm_mv*F/(R*T)) - 1); // 0.75 - for instant activation !

}

void am_cell::calc_IK(double time_step, int solve_method) {
	double alpha_pa, beta_pa, pa_inf, tau_pa;
	double alpha_pi, beta_pi, pi_inf, tau_pi;
	double alpha_n, beta_n, n_inf, tau_n;
	double vm_mv = get_vm() * 1000;
	//IKf
	alpha_pa = 9.0 * exp(vm_mv / 25.371);
	beta_pa = 1.3 * exp(-vm_mv / 13.026);
	pa_inf = 1. / (1 + exp(-(vm_mv + 5.1) / 7.4));
	tau_pa = 1000. / (alpha_pa + beta_pa);
	Pa += HT * (pa_inf - Pa) / tau_pa;
	alpha_pi = 100. * exp(-vm_mv / 54.645);
	beta_pi = 656. * exp(vm_mv / 106.157);
	pi_inf = alpha_pi / (alpha_pi + beta_pi);
	tau_pi = 1000.0 / (alpha_pi + beta_pi);
	Pi += HT * (pi_inf - Pi) / tau_pi;
	//Iks
	alpha_n = 1.66 * exp(vm_mv / 69.452);
	beta_n = 0.3 * exp(-vm_mv / 21.826);
	n_inf = 1.0 / (1 + exp(-(vm_mv - 0.9) / 13.8));
	tau_n = 1000 * (1. / (alpha_n + beta_n) + 0.06);
	n += HT * (n_inf - n) / tau_n;
	double IKs, IKf;
	IKs = G_Ks * n * (vm_mv - EK);
	IKf = 3.5 * Pa * Pi * (vm_mv - EK); //ikr = 0 sometimes!
	IK = IKf + IKs;
}

void am_cell::calc_Ik1(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	double E0 = vm_mv - EK + 3.6;
	Ik1 = get_g_k1() * pow(KIono / (KIono + 0.59), 3) * (vm_mv - EK) / (1 + exp((F/(R*T)) * 1.393 * E0));
}

void am_cell::calc_Ito(double time_step, int solve_method) {
	double alpha_r, beta_r, r_inf, tau_r;
	double s1_inf, tau_s1, s2_inf, tau_s2, s3_inf, tau_s3;
	double vm_mv = get_vm() * 1000;
	//Ito

	r_inf = 1 / (1 + exp((vm_mv +15.) / -5.633));
	alpha_r = 386.6 * exp(vm_mv / 12.0);
	beta_r = 8.011 * exp(-vm_mv / 7.2);
	tau_r = 1000 * (1. / (alpha_r + beta_r) + 0.0004);

	r1 += HT * (r_inf - r1) / tau_r;

	s1_inf = 1. / (1 + exp((vm_mv + 28.29) / 7.06));
	tau_s1 = 1000 * (0.189 / (1 + exp((vm_mv + 32.8) / 0.1)) + 0.0204);
	s1 += HT * (s1_inf - s1) / tau_s1;

	s2_inf = 1. / (1 + exp((vm_mv + 28.29) / 7.06));
	tau_s2 = 1000 * (5.75 / (1 + exp((vm_mv + 32.8) / 0.1)) + 0.02 + 0.45 / (1 + exp(-(vm_mv - 13.54) / 13.97)));
	s2 += HT * (s2_inf - s2) / tau_s2;

	s3_inf = ((1. / (1 + exp((vm_mv + 50.67) / 27.38))) + 0.666) / 1.666;
	tau_s3 = 1000 * ((7.5 / (1 + exp((vm_mv + 23.0) / 0.5))) + 0.5);
	s3 += HT * (s3_inf - s3) / tau_s3;

	Ito = get_g_to() * r1 * (0.590 * pow(s1, 3) + 0.410 * pow(s2, 3)) * (0.600 * pow(s3, 6) + 0.4) * (vm_mv - EK);    // CT - 0.2, PM - 0.35

}

void am_cell::calc_INaCa(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	INaCa = get_g_naca() * (((NaIoni * NaIoni * NaIoni) * 2.5 * exp(0.450 * vm_mv / RTF) - (140.0 * 140.0 * 140.0) * CaIoni * exp(vm_mv * (0.45 - 1) / RTF)) / (1 + 0.0003 * (CaIoni * (140.0 * 140.0 * 140.0) + 2.5 * (NaIoni * NaIoni * NaIoni))));
}
void am_cell::calc_Ip(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	Ip = get_g_nak() * KIono / (KIono + 1) * (pow(NaIoni, 1.5) / (pow(NaIoni, 1.5) + pow(11, 1.5))) * ((vm_mv+150)/(vm_mv+200));
}

void am_cell::calc_Ib(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	Ib = get_g_b_na() * (vm_mv - ENa) + get_g_b_ca() * (vm_mv - ECa) + Gb_Cl * (vm_mv - ECl)*(1+exp((vm_mv-(ECl + 36.95))/74.514)); // 0.02 - CT, 0.03 - PM
}

void am_cell::calc_ICap(double time_step, int solve_method) {
	ICap = G_Cap_MAX * (CaIoni / (CaIoni + 0.002));
}

void am_cell::calc_ICaL(double time_step, int solve_method) {
	double alpha_dl, beta_dl, beta_fl, dl_inf, tau_dl,alpha_fl;
	double fl_inf,tau_fl;
	double vm_mv = get_vm() * 1000;
	//ICaL
	
	alpha_dl = -16.72 * (vm_mv + 35) / (exp(-(vm_mv + 35) / 2.5) - 1) - 50.0 * vm_mv / (exp(-vm_mv / 4.808) - 1);


	beta_dl = 4.48 * (vm_mv - 5) / (exp((vm_mv - 5) / 2.5) - 1.);

	tau_dl = 1000. / (alpha_dl + beta_dl);

	dl_inf = 1. / (1 + exp(-(vm_mv + 0.95) / 6.6));

	dL += HT * (dl_inf - dL) / tau_dl;


	alpha_fl = 8.49 * (vm_mv + 28) / (exp((vm_mv + 28) / 4) - 1.);

	beta_fl = 67.922 / (1 + exp(-(vm_mv + 28) / 4));
	fl_inf = alpha_fl / (alpha_fl + beta_fl);
	tau_fl = 0.211 * exp(-pow(((vm_mv+37.427)/20.213),2)) + 0.015;
	tau_fl *= 1000;
	fL += HT * (fl_inf - fL) / tau_fl;
	vm_mv += 20;
	ICaL = get_g_ca() * (dL * fL + 1.0 / (1 + exp(-(vm_mv - 33.0) / 12.0))) * (vm_mv - 60);
}

void am_cell::calc_ICaT(double time_step, int solve_method) {
	double alpha_dt, beta_dt, dt_inf, tau_dt;
	double alpha_ft, beta_ft, ft_inf, tau_ft;
	double vm_mv = get_vm() * 1000;
	//ICaT
	alpha_dt = 674.173 * exp((vm_mv + 23.3) / 30.);
	beta_dt = 674.173 * exp(-(vm_mv + 23.3) / 30.);
	tau_dt = 1000. / (alpha_dt + beta_dt);
	dt_inf = 1. / (1 + exp(-(vm_mv + 23.0) / 6.1));
	dT += HT * (dt_inf - dT) / tau_dt;
	alpha_ft = 9.637 * exp(-(vm_mv + 75) / 83.3);
	beta_ft = 9.637 * exp((vm_mv + 75) / 15.38);
	tau_ft = 1000.0 / (alpha_ft + beta_ft);
	ft_inf = alpha_ft / (alpha_ft + beta_ft);
	fT += HT * (ft_inf - fT) / tau_ft;
	ICaT = G_CaT * dT * fT * (vm_mv - 38);
}

void am_cell::calc_Isus(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	Isus = 1.3 * (vm_mv + 70);
}
void am_cell::calc_i_b_na(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	i_b_na = get_P_na() * vm_mv * ((pow(F, 2.0)) / (R * 1000 * T)) * ((NaIoni - ((NaIono)*exp(-(F * vm_mv) / (R * 1000 * T)))) / (1 - (exp(-(vm_mv * F) / (R * 1000 * T)))));
}