#pragma once
#include "useful_functions.h"
using namespace std;

int find_value(vector<double> value_vector, double value_to_find) {
	double vector_length = value_vector.size();
	for (int i{}; i < vector_length; i++) {
		if (value_vector[i] == value_to_find) {
			return i;
		}
	}
	cout << "Could not find value exactly, switching to closest value..." << endl;
	double smallest_difference{ 100 };
	int smallest_difference_index;
	for (int i{}; i < vector_length; i++) {
		double difference{ abs(value_vector[i] - value_to_find) };
		if (difference < smallest_difference) {
			smallest_difference = difference;
			smallest_difference_index = i;
		}
	}
	if (smallest_difference != 100) {
		cout << "Closest value to " << value_to_find << " is " << value_vector[smallest_difference_index] << ". Returning out of function." << endl;
		return smallest_difference_index;
	}
	else {
		cout << "ERROR: Could not find any value..? Exiting...";
		exit(0);

	}
}

int find_value_min_index(vector<double> value_vector, double value_to_find, int min_index) {
	double vector_length = value_vector.size();
	for (int i{ min_index }; i < vector_length; i++) {
		if (value_vector[i] == value_to_find) {
			return i;
		}
	}
	cout << "Could not find value exactly, switching to closest value..." << endl;
	double smallest_difference{ 100 };
	int smallest_difference_index;
	for (int i{ min_index }; i < vector_length; i++) {
		double difference{ abs(value_vector[i] - value_to_find) };
		if (difference < smallest_difference) {
			smallest_difference = difference;
			smallest_difference_index = i;
		}
	}
	if (smallest_difference != 100) {
		cout << "Closest value to " << value_to_find << " is " << value_vector[smallest_difference_index] << ". Returning out of function." << endl;
		return smallest_difference_index;
	}
	else {
		cout << "ERROR: Could not find any value..? Exiting...";
		exit(0);

	}
}

void print_cell_type(int celltype) {
	if (celltype == 1) {
		cout << "\nSimulating an N type cell..." << endl;
	}
	else if (celltype == 16) {
		cout << "\nSimulating an AN type cell..." << endl;
	}
	else if (celltype == 19) {
		cout << "\nSimulating an NH type cell..." << endl;
	}
	else {
		cout << "\nSimulating an unknown cell type, " << celltype << "..." << endl;
	}
}