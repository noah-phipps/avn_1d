/*--------------------------------------------------------------------
-------- -
AM Cell Action Potential Model
21 / 03 / 2021 Modified by Noah PHIPPS and Gemma LAMB (Removing depreceated C style code, optimising functions, formatting, generally rewritten)
22 / 03 / 2021 Rewritten by Noah PHIPPS and Gemma LAMB (Created functions for currents)
--------------------------------------------------------------------
------ */
#include "cell_base.h"
#include <math.h>
#include"configuration.h"
#include<fstream>
#include<iostream>
#define HT coarse_time_step
#define R_am 8314.472
#define T_am 310
#define F_am 96484.6
#define RTOnF (R_am*T_am/F_am)

class am_cell :public cell_base {
	//Constants
	const double dNaCa = 0.0001;
	//reversal potentials
	const double ECaL = 46.4;   // mV
	const double ECaT = 45;     // mV

	/// intracelular and extracellular concentration
	const double Nao = 140;         // mM
	const double Nai = 8;
	const double Cao = 2;
	const double Cai = 0.0001;//0.0001
	const double Ko = 5.4;//5.4
	const double Ki = 90;//140
	const double Clo = 130;//132
	const double Cli = 15.0;//30
	const double KmK = 0.621;
	const double KmNa = 5.64;
	const double yNaCa = 0.5;

	const double gAchperiphery = 0.0792 * 1.0E3;
	//Variables
	const double ENa = RTOnF * log(Nao / Nai);
	const double ECa = 0.5 * RTOnF * log(Cao / Cai);
	const double EK = RTOnF * log(Ko / Ki);
	const double EKs = RTOnF * log((Ko + 0.003 * Nao) / (Ki + 0.03 * Nai));
	const double ECl = RTOnF * log(Cli/Clo);

	const double aj = 73.1;   //Ach rate constant
	const double ak = 3.7;    //Ach rate constant
	//double Ach =2.0e-7;
	double Ach = 0.0;

	double INa{}, IK{}, IKf{}, IKs{}, Ik1{}, Ito{}, INaCa{}, Ip{}, Ib{}, ICaL{}, ICaT{}, Isus{}, IbNa{}, IbCa{}, IAch{}, IbCl{};//Change

	double m, h1, h2, dL, fL, dT, fT, r, paf, pi, n, s1, s2, s3, sj, sk;

public:
	am_cell(int);
	am_cell() {
		set_cell_type(2);
		set_cm(50);
		set_vm(-80.33126E-3);
		paf = 0.000038;
		pi = 0.853868;
		n = 0.002822;
		r = 0.000009;
		s1 = 0.865802;
		s2 = 0.492230;
		s3 = 0.645536;
		m= 0.003278;
		h1 = 0.973246;
		h2 = 0.972437;
		dL = 0.000027;
		fL = 0.999989;
		dT = 0.000083;
		fT = 0.601143;
		sj = 0.38030237413008;
		sk= 0.48075923797918;
		Ach = 0.0;
		set_i_stim(0);//0 when initialising
		set_coupling_conductance(0);//Only needed in 1D; set in main
		set_g_na(1.);//Truly a factor for P_na
		set_g_ca(6);//For ICaL
		set_g_kr(0);//Unused
		set_g_st(0);//Unused
		set_g_b(0);//Unused
		set_g_b_na(0.02);//.02
		set_g_b_ca(0.02);//.02
		set_p_max(0);//Unused
		set_k_naca(0.02);//Used for g_NaCa
		set_P_na(0.0014);
		set_g_nak(64.41);//Used for Ip
	}
	void export_cell(int);
	void calc_i_all(double, int, int);
	double get_total_ion(bool i_bna_zero);
	void initialise() {
		set_cell_type(2);
		set_cm(50);
		set_vm(-80.33126E-3);
		paf = 0.000038;
		pi = 0.853868;
		n = 0.002822;
		r = 0.000009;
		s1 = 0.865802;
		s2 = 0.492230;
		s3 = 0.645536;
		m = 0.003278;
		h1 = 0.973246;
		h2 = 0.972437;
		dL = 0.000027;
		fL = 0.999989;
		dT = 0.000083;
		fT = 0.601143;
		sj = 0.38030237413008;
		sk = 0.48075923797918;
		Ach = 0.0;
		set_i_stim(0);//0 when initialising
		set_coupling_conductance(0);//Only needed in 1D; set in main
		set_g_na(1.0);//Truly a factor for P_na
		set_g_ca(6);//For ICaL
		set_g_kr(0);//Unused
		set_g_st(0);//Unused
		set_g_b(0);//Unused
		set_g_b_na(0.02);
		set_g_b_ca(0.02);
		set_p_max(0);//Unused
		set_k_naca(0.02);//Used for g_NaCa
		set_P_na(0.0014);
		set_g_nak(64.41);//Used for Ip
	}
	void print_currents(std::ofstream&, double, int);
	void calc_INa(double, int);
	void calc_IK(double, int);
	void calc_Ik1(double, int);
	void calc_Ito(double, int);
	void calc_INaCa(double, int);
	void calc_Ip(double, int);
	void calc_Ib(double, int);
	void calc_ICaL(double, int);
	void calc_ICaT(double, int);
	void calc_Isus(double, int);
	void calc_i_ach(double, int);
	void zero_currents();
	void zero_variables();
	double get_i_na(){
		return INa;
	}
	double get_i_cal() {
		return ICaL;
	}
	void reset();
	double get_i_k1() { return Ik1; }
	double get_i_to() { return Ito; }
	double get_i_kr() { return IKf; }
	double get_i_naca() { return INaCa; }
};