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
	//r1 = import_parameters[1];
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
	//Pa = import_parameters[13];
	//Pi = import_parameters[14];
	EK = import_parameters[15];
	ENa = import_parameters[16];
	ECa = import_parameters[17];
	//ECl = import_parameters[18];
	//EbCl = import_parameters[19];
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
	//i_b_na = import_parameters[31];
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
	//export_parameters[1] = r1;
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
	//export_parameters[13] = Pa;
	//export_parameters[14] = Pi;
	export_parameters[15] = EK;
	export_parameters[16] = ENa;
	export_parameters[17] = ECa;
	//export_parameters[18] = ECl;
	//export_parameters[19] = EbCl;
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
	//export_parameters[31] = i_b_na;
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

void am_cell::print_ions(std::ofstream& output_file, double time) {
	std::cout << "Error, no implementation";
}

double am_cell::get_total_ion(bool i_bna_zero) {
	return (IKf + IKs + Ik1 + Ito + Ip + INaCa + INa + IbNa + IbCa + ICaL + ICaT + IAch);
}

void am_cell::calc_i_all(double time_step, int solve_method, int l) {
	calc_IK(time_step, solve_method);
	calc_INa(time_step, solve_method);
	calc_Ik1(time_step, solve_method);
	calc_Ito(time_step, solve_method);
	calc_INaCa(time_step, solve_method);
	calc_Ip(time_step, solve_method);
	calc_Ib(time_step, solve_method);
	calc_ICaL(time_step, solve_method);
	calc_ICaT(time_step, solve_method);
	calc_Isus(time_step, solve_method);
	calc_i_ach(time_step, solve_method);

}

void am_cell::calc_INa(double time_step, int solve_method) {
	double Am, Bm;
	double Ah, Bh;
	double hm, mm;
	double th1, th2;
	double vm_mv = get_vm() * 1000;
	if (fabs(vm_mv + 44.4) < 0.0001)
		Am = 460. * 12.673;
	else
		Am = -460. * (vm_mv + 44.4) / (exp(-(vm_mv + 44.4) / 12.673) - 1);
	Bm = 18400.0 * exp(-(vm_mv + 44.4) / 12.673);
	m = Am / (Am + Bm);

	Ah = 44.9 * exp(-(vm_mv + 66.9) / 5.57);
	Bh = 1491.0 / (1 + 323.3 * exp(-(vm_mv + 94.6) / 12.9));

	th1 = 0.03 / (1 + exp((vm_mv + 40) / 6.0)) + 0.00015;  // 0.00035
	th2 = 0.12 / (1 + exp((vm_mv + 60) / 2.0)) + 0.00045;  // 0.00295
	hm = Ah / (Ah + Bh);
	h1 = h1 + HT * (hm - h1) / th1;
	h2 = h2 + HT * (hm -h2) / th2;

	if (fabs(vm_mv) > 0.0001)
		INa = 0.8 * 0.0014 * pow(m, 3) * (0.635 * h1 + 0.365 * h2) * 140 * vm_mv * (F / RTOnF) * (exp((vm_mv - ENa) / RTOnF) - 1) / (exp(vm_mv/ RTOnF) - 1);  // 0.8
	else INa = 0.8 * 0.0014 * pow(m, 3) * (0.635 * h1 + 0.365 * h2) * 140 * F * (exp((vm_mv - ENa) / RTOnF) - 1);                                             // 0.8  

}

void am_cell::calc_IK(double time_step, int solve_method) {
	double Apa, Bpa;
	double pam, tpa;
	double Api, Bpi;
	double pim, tpi;
	double An, Bn;
	double nm, tn;
	double vm_mv = get_vm() * 1000;
	Apa = 9.0 * exp(vm_mv/ 25.371);
	Bpa = 1.3 * exp(vm_mv / 13.026);
	pam = 1. / (1 + exp(-(vm_mv + 5.1) / 7.4));
	tpa = 1. / (Apa + Bpa);
	paf = paf + HT * (pam - paf) / tpa;

	Api = 100. * exp(vm_mv / 54.645);
	Bpi = 656. * exp(vm_mv / 106.157);
	pim = 1. / (1 + exp((vm_mv + 47.3921) / 18.6603));
	tpi = 1.0 / (Api + Bpi);
	pi = pi + HT * (pim - pi) / tpi;

	IKf = 3.5 * paf* pi * (vm_mv- EK);

	An = 1.66 * exp(vm_mv / 69.452);
	Bn = 0.3 * exp(vm_mv / 21.826);
	nm = 1.0 / (1 + exp(-(vm_mv - 0.9) / 13.8));
	tn = 1. / (An + Bn) + 0.06;
	n = n + HT * (nm - n) / tn;

	IKs = 2.5 * n* (vm_mv - EK);

	IK = IKf + IKs;
}

void am_cell::calc_Ik1(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	Ik1 = 10.16 * pow(Ko / (Ko + 0.59), 3) * (vm_mv - EK) / (1 + exp(1.393 * (vm_mv - EK + 3.6) / RTOnF));

}

void am_cell::calc_Ito(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	double Ar, Br;
	double rm, tr;
	double s1m, ts1;
	double s2m, ts2;
	double s3m, ts3;

	Ar = 386.6 * exp(vm_mv / 12.0);
	Br = 8.011 * exp(vm_mv / 7.2);
	rm = 1 / (1 + exp(-(vm_mv + 15.0) / 5.633));
	tr = 1. / (Ar + Br) + 0.0004;
	r = r + HT * (rm - r) / tr;

	s1m = 1. / (1 + exp((vm_mv + 28.29) / 7.06));
	ts1 = 0.5466 / (1 + exp((vm_mv + 32.8) / 0.1)) + 0.0204;
	s1 = s1 + HT * (s1m - s1) / ts1;

	s2m = 1. / (1 + exp((vm_mv + 28.29) / 7.06));
	ts2 = 5.75 / (1 + exp((vm_mv+ 32.8) / 0.1)) + 0.45 / (1 + exp(-(vm_mv - 13.54) / 13.97));
	s2 = s2 + HT * (s2m - s2) / ts2;

	s3m = ((1. / (1 + exp((vm_mv + 50.67) / 27.38))) + 0.666) / 1.666;
	ts3 = (7.5 / (1 + exp((vm_mv + 23.0) / 0.5))) + 0.5;
	s3 = s3 + HT * (s3m - s3) / ts3;
	Ito = 10.004 * r * (0.590 * pow(s1, 3) + 0.410 * pow(s2, 3)) * (0.600 * pow(s3, 6) + 0.4) * (vm_mv - EK);
	Isus = 1.3 * (vm_mv + 70);
	Ito += Isus;
}

void am_cell::calc_INaCa(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	INaCa = 0.02 * (pow(Nai, 3) * 2.5 * exp(0.450 * vm_mv / RTOnF) - pow(140, 3) * Cai * exp(vm_mv * (0.45 - 1) / RTOnF)) / (1 + 0.0003 * (Cai * pow(140, 3) + 2.5 * pow(Nai, 3)));

}
void am_cell::calc_Ip(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	Ip = 64.41 * Ko / (Ko + 1) * (pow(Nai, 1.5) / (pow(Nai, 1.5) + pow(11, 1.5))) * (1.6 / (1.5 + exp(-(vm_mv + 60) / 40.)));

}

void am_cell::calc_Ib(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;

	IbNa = 0.02 * (vm_mv - ENa);

	IbCa = 0.02 * (vm_mv - ECa);

	Ib = IbNa + IbCa;
}

void am_cell::calc_ICap(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	std::cout << "Error, no implementation";
}

void am_cell::calc_ICaL(double time_step, int solve_method) {
	double Adl, Bdl;
	double dlm, tdl;
	double Afl, Bfl;
	double flm, tfl;
	double B;
	double vm_mv = get_vm() * 1000;
	vm_mv = vm_mv + 10;
	Adl = -16.72 * (vm_mv + 35) / (exp(-(vm_mv + 35) / 2.5) - 1) - 50.0 * vm_mv / (exp(-vm_mv / 4.808) - 1);
	if (fabs(vm_mv + 35) < 0.0001)
		Adl = 16.72 * 2.5 - 50.0 * vm_mv / (exp(-vm_mv / 4.808) - 1);
	if (fabs(vm_mv) < 0.0001)
		Adl = -16.72 * (vm_mv + 35) / (exp(-(vm_mv + 35) / 2.5) - 1) + 50.0 * 4.808;

	if (fabs(vm_mv - 5.) < 0.0001)
		Bdl = 4.48 * 2.5;
	else
		Bdl = 4.48 * (vm_mv - 5) / (exp((vm_mv - 5) / 2.5) - 1.);
	tdl = 1 / (Adl + Bdl);

	dlm = 1. / (1 + exp(-(vm_mv + 0.95) / 6.6));
	dL = dL + HT * (dlm - dL) / tdl;

	vm_mv = vm_mv - 10;
	vm_mv = vm_mv - 10;

	if (fabs(vm_mv + 28) < 0.0001)
		Afl = 8.49 * 4;
	else
		Afl = 8.49 * (vm_mv + 28) / (exp((vm_mv + 28) / 4) - 1.);
	Bfl = 67.922 / (1 + exp(-(vm_mv + 28) / 4));

	flm = Afl / (Afl + Bfl);
	tfl = 1.0 / (Afl + Bfl);
	fL =fL + HT * (flm - fL) / tfl;

	vm_mv = vm_mv + 10;
	vm_mv = vm_mv + 10;
	B = 0.56 * (Ach / (1.2e-7 + Ach));  //b Ach effect

	ICaL = (1 - B) * 7.2 * (dL * fL + 1.0 / (1 + exp(-(vm_mv- 33.0) / 12.0))) * (vm_mv- 60);
}

void am_cell::calc_ICaT(double time_step, int solve_method) {
	double Adt, Bdt;
	double dtm, tdt;
	double Aft, Bft;
	double ftm, tft;
	double vm_mv = get_vm() * 1000;
	Adt = 674.173 * exp((vm_mv + 23.3) / 30.);
	Bdt = 674.173 * exp(-(vm_mv + 23.3) / 30.);
	tdt = 1 / (Adt + Bdt);

	dtm = 1. / (1 + exp(-(vm_mv + 23.0) / 6.1));
	dT = dT + HT * (dtm - dT) / tdt;

	Aft = 9.637 * exp(-(vm_mv + 75) / 83.3);
	Bft = 9.637 * exp((vm_mv + 75) / 15.38);
	tft = 1.0 / (Aft + Bft);
	ftm = Aft / (Aft + Bft);
	fT = fT + HT * (ftm - fT) / tft;

	ICaT = 6.0 * dT* fT * (vm_mv - 38.0);
}

void am_cell::calc_Isus(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	Isus = 1.3 * (vm_mv + 70);
}
void am_cell::calc_i_b_na(double time_step, int solve_method) {
	double vm_mv = get_vm() * 1000;
	std::cout<< "Error: No implementation";
}

void am_cell::calc_intracellular_dynamics() {
	std::cout << "Error: No implementation";

}

void am_cell::calc_i_ach(double time_step, int solve_method) {
	double Bj, Bk;
	double gAch;
	double vm_mv = get_vm() * 1000;

	Bj = 120. / (1 + exp(-(vm_mv + 50) / 15.));
	Bk = 5.82 / (1 + exp(-(vm_mv + 50) / 15.0));
	sj = sj + HT * (aj * (1 - sj) - Bj * sj);
	sk = sk + HT * (ak * (1 - sk) - Bk * sk);
	gAch = gAchperiphery * sj * sk * (Ach / (2.0e-7 + Ach));
	IAch = gAch * (Ko / (10 + Ko)) * (vm_mv - EK) / (1 + exp(1 * (vm_mv - EK - 140) / (2.5 * RTOnF)));
}