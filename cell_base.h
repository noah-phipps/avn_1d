/*--------------------------------------------------------------------
-------- -
Cell Base Abstract Class
21 / 03 / 2021 Modified by Noah PHIPPS and Gemma LAMB (Removing depreceated C style code, optimising functions, formatting, generally rewritten)
--------------------------------------------------------------------
------ */
#ifndef CELL_BASE_H
#define CELL_BASE_H
#define NEGLIGIBLE_SMALL pow(10,-5)
#define F 96487 // Faraday's constant
#define R 8.314 // Universal gas constant 8.314
#define T 308 // Absolute temperature
#define RTF 26.539
#include<string>

class cell_base {
	double vm{};
	double vm_1{};
	double cm{};
	int cell_type{};
	double i_stim{};
	double ca_out{};
	double na_out{};
	double k_out{};
	double na_in{};
	double ca_in{};
	double k_in{};
	double rev_na{}, rev_k{}, rev_ca{};
	double coupling_conductance{};
	double g_l{}, g_to{}, g_kr{}, g_naca{}, g_k1{}, g_b_na{}, g_b_ca{},
		g_nak{}, p_max{}, k_naca{}, P_na{}, g_b{}, g_st{}, g_na{};
public:
	double get_vm() {
		return vm;
	}
	double get_vm_1() {
		return vm_1;
	}
	void set_vm(double input_vm) {
		vm = input_vm;
	}
	void set_vm_1(double input_vm_1) {
		vm_1 = input_vm_1;
	}
	void set_i_stim(double input_i_stim) {
		i_stim = input_i_stim;
	}
	void set_p_max(double p) {
		p_max = p;
	}
	void set_k_naca(double k) {
		k_naca = k;
	}
	void set_g_ca(double g) {
		g_l = g;
	}
	void set_g_kr(double g) {
		g_kr = g;
	}
	void set_P_na(double P) {
		P_na = P;
	}
	void set_g_b_na(double g) {
		g_b_na = g;
	}
	void set_g_to(double g) {
		g_to = g;
	}
	void set_g_k1(double g) {
		g_k1 = g;
	}
	void set_g_naca(double g) {
		g_naca = g;
	}
	void set_g_nak(double g) {
		g_nak = g;
	}
	void set_g_b_ca(double g) {
		g_b_ca = g;
	}
	void set_g_b(double g) {
		g_b = g;
	}
	void set_g_st(double g) {
		g_st = g;
	}
	void set_g_na(double g) {
		g_na = g;
	}
	double get_g_na() {
		return g_na;
	}
	double get_P_na() {
		return P_na;
	}
	double get_g_nak() {
		return g_nak;
	}
	double get_g_naca() {
		return g_naca;
	}
	double get_g_b_na() {
		return g_b_na;
	}
	double get_g_b_ca() {
		return g_b_ca;
	}
	double get_g_ca() {
		return g_l;
	}
	double get_g_kr() {
		return g_kr;
	}
	double get_g_to() {
		return g_to;
	}
	double get_g_st() {
		return g_st;
	}
	double get_k_naca() {
		return k_naca;
	}
	double get_g_b() {
		return g_b;
	}
	double get_g_k1() {
		return g_k1;
	}
	double get_p_max() {
		return p_max;
	}
	void set_ca_in(double input_ca_in) {
		ca_in = input_ca_in;
	}
	double get_ca_in() {
		return ca_in;
	}
	void set_na_in(double input_na_in) {
		na_in = input_na_in;
	}
	double get_na_in() {
		return na_in;
	}
	void set_k_in(double input_k_in) {
		k_in = input_k_in;
	}
	double get_k_in() {
		return k_in;
	}
	void set_ca_out(double input_ca_out) {
		ca_out = input_ca_out;
	}
	double get_ca_out() {
		return ca_out;
	}
	void set_na_out(double input_na_out) {
		na_out = input_na_out;
	}
	double get_na_out() {
		return na_out;
	}
	void set_k_out(double input_k_out) {
		k_out = input_k_out;
	}
	double get_k_out() {
		return k_out;
	}
	void set_cm(double input_cm) {
		cm = input_cm;
	}
	double get_cm() {
		return cm;
	}
	void set_cell_type(int input_cell_type) {
		cell_type = input_cell_type;
	}
	int get_cell_type() {
		return cell_type;
	}
	void set_rev_na(double rev) {
		rev_na = rev;
	}
	void set_rev_ca(double rev) {
		rev_ca = rev;
	}
	void set_rev_k(double rev) {
		rev_k = rev;
	}
	double get_rev_na() {
		return rev_na;
	}
	double get_rev_k() {
		return rev_k;
	}
	double get_rev_ca() {
		return rev_ca;
	}
	double get_i_stim() {
		return i_stim;
	}
	virtual void calc_i_all(double, int, int) = 0;
	virtual double get_total_ion(bool) = 0;
	void calc_vm(double time_step, int solve_method, bool i_bna_zero) {
		double vm = (*this).get_vm();
		double I = (*this).get_total_ion(i_bna_zero) + (*this).get_i_stim();

		double cm = (*this).get_cm();
		double diff_vm = -I / cm;
		//vm = solve_diff_eqn(vm, diff_vm, time_step, solve_method);
		(*this).set_vm(vm+diff_vm*time_step);
	}
	void set_coupling_conductance(double g) {
		coupling_conductance = g;
	}
	double get_coupling_conductance() {
		return coupling_conductance;
	}
	double solve_diff_eqn(double x, double diff_x, double time_step, int solve_method) {
		x = x + time_step * diff_x;
		return x;
	}
	void block_na(double f) {
		g_na = f * g_na;
	}
	void block_ca(double f) {
		g_l = f * g_l;
	}
	virtual void export_cell(int) = 0;
	virtual void print_currents(std::ofstream&,double,int) = 0;
	virtual double get_i_na() = 0;
	virtual double get_i_cal() = 0;
	virtual void reset() = 0;
	virtual double get_i_k1() = 0;
	virtual double get_i_to() = 0;
	virtual double get_i_kr() = 0;
	virtual double get_i_naca() = 0;
};

#endif