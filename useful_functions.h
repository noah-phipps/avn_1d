#pragma once
#include<vector>
#include<iostream>
using namespace std;

int find_value(vector<double> value_vector, double value_to_find);

int find_value_min_index(vector<double> value_vector, double value_to_find, int min_index);

void print_cell_type(int celltype);