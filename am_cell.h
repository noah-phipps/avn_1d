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
#define HT coarse_time_step
#define R2 8314
class am_cell :public cell_base {
	double n, r1, s1, s2, s3, m, h1, h2, dL, fL, dT, fT, Pa,Pi;//These change
	double G_CaT, G_Cap_MAX, G_Ks, Gb_Cl, CaIoni, KIono, KIoni,
		NaIoni, NaIono, CaIono;//Static
	double EK, ENa, ECa, ECl, EbCl;//Change
	double INa{}, IK{}, Ik1{}, Ito{}, INaCa{}, Ip{}, Ib{}, ICap{}, ICaL{}, ICaT{},
		Isus{};//Change
	double i_b_na{};//Change
public:
	am_cell(int);
	am_cell() {
		set_vm(-69.83663E-3);
		set_cm(50);
		set_i_stim(0);
		n = .02032;
		r1 = 0.00006;
		s1 = 0.57530;
		s2 = 0.39871;
		s3 = 0.57363;
		m = 0.01309;
		h1 = 0.706;
		h2 = 0.61493;
		dL = 0.00003;
		fL = 0.99981;
		dT = 0.00016;
		fT = 0.30752;
		Pa = 3.533e-5;
		Pi = .76898;
		set_cell_type(2);
		set_P_na(0.0014E-6);
		set_g_na(1);//Not accessed by AM cell
		set_g_ca(4);
		G_CaT = 6.0;
		set_g_to(50.002);
		set_g_kr(3.5);
		G_Cap_MAX = 9.509;
		set_g_naca(0.02);
		G_Ks = 2.5;
		set_g_k1(5.088);
		set_g_b_na(0.064);
		set_g_b_ca(0.031);
		Gb_Cl = 0.120;
		set_g_nak(64.41);
		CaIoni = 0.00007305;
		KIono = 5.0;
		KIoni = 100.0;
		NaIoni = 8.4;
		NaIono = 140;
		CaIono = 2.5;
		EK = RTF * log(KIono / KIoni);
		ENa = RTF * log(NaIono / NaIoni);
		ECa = (RTF / 2.) * log(CaIono / CaIoni);
		ECl = RTF * log(30. / 132.);
		EbCl = ECl - 0.49 * (ECl - 30.59);
	}
	void export_cell(int);
	void calc_i_all(double, int, int);
	double get_total_ion(bool i_bna_zero);
	void initialise() {
		set_vm(-69.83663E-3);
		set_cm(50);
		set_i_stim(0);
		n = .02032;
		r1 = 0.00006;
		s1 = 0.57530;
		s2 = 0.39871;
		s3 = 0.57363;
		m = 0.01309;
		h1 = 0.706;
		h2 = 0.61493;
		dL = 0.00003;
		fL = 0.99981;
		dT = 0.00016;
		fT = 0.30752;
		Pa = 3.533e-5;
		Pi = .76898;
		set_cell_type(2);
		set_P_na(0.0014E-6);
		set_g_na(1);//Not accessed by AM cell
		set_g_ca(4);
		G_CaT = 6.0;
		set_g_to(50.002);
		set_g_kr(3.5);
		G_Cap_MAX = 9.509;
		set_g_naca(0.02);
		G_Ks = 2.5;
		set_g_k1(5.088);
		set_g_b_na(0.064);
		set_g_b_ca(0.031);
		Gb_Cl = 0.120;
		set_g_nak(64.41);
		CaIoni = 0.00007305;
		KIono = 5.0;
		KIoni = 100.0;
		NaIoni = 8.4;
		NaIono = 140;
		CaIono = 2.5;
		EK = RTF * log(KIono / KIoni);
		ENa = RTF * log(NaIono / NaIoni);
		ECa = (RTF / 2.) * log(CaIono / CaIoni);
		ECl = RTF * log(30. / 132.);
		EbCl = ECl - 0.49 * (ECl - 30.59);
	}
	void print_currents(std::ofstream&, double, int);
	void calc_INa(double, int);
	void calc_IK(double, int);
	void calc_Ik1(double, int);
	void calc_Ito(double, int);
	void calc_INaCa(double, int);
	void calc_Ip(double, int);
	void calc_Ib(double, int);
	void calc_ICap(double, int);
	void calc_ICaL(double, int);
	void calc_ICaT(double, int);
	void calc_Isus(double, int);
	void calc_i_b_na(double, int);
};