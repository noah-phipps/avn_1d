#include "cell_base.h"
#include <iostream>
void cell_base::calc_vm(double time_step, int solve_method, bool
	i_bna_zero) {
	double vm = (*this).get_vm();
	double I = (*this).get_total_ion(i_bna_zero) +
		(*this).get_i_stim();
	double cm = (*this).get_cm();
	double diff_vm = -I / cm;
	vm = solve_diff_eqn(vm, diff_vm, time_step, solve_method);
	(*this).set_vm(vm);
}

double cell_base::solve_diff_eqn(double x, double diff_x, double time_step, int solve_method) {
	x = x + time_step * diff_x;
	if (isnan(x)) {
		std::cout << "ISNAN ERROR IN SOLVE DIFF";
	}
	return x;
}
