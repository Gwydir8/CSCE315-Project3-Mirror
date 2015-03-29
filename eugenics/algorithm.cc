#include <vector>
#include <queue>
#include "circuit.h"
using namespace std;

// initalize base circuit into exhaustive list
std::queue<Circuit> ex_list;
std::vector<bool> init = {0, 0, 0};
Circuit base (init, 0);
ex_list.push(base);

int level = 1;
int not_counter = 3;

int check_output(Circuit x, vector<bool> sum, vector<bool> c_out) {

	// assuming that sum and c_out are the same length
	int size = sum.size();
	
	for(int i = 0; i < size; ++i) {
		if (x.evaluateInputSet(sum)[i] == true && x.evaluateInputSet(c_out)[i] == true);
		// if doesn't equal desired output
		else 
			return 0;
	}

	// if it equals desired output
	return 1;
}

void add_not(int counter) {
	for(int i = 0; i < counter; ++i) {
		Circuit next = ex_list.front();
		next.addGate(NOT, i);
		ex_list.push(next);
	}
}

void add_and(int counter) {
	for(int i = 0; i < counter; ++i) {
		Circuit next = ex_list.front();
		next.addGate(AND, i);
		ex_list.push(next);
	}
}

void add_or(int counter) {
	for(int i = 0; i < counter; ++i) {
		Circuit next = ex_list.front();
		next.addGate(OR, i);
		ex_list.push(next);
	}
}

Circuit search(vector<bool> sum, vector<bool> c_out) {

	// keeps track of # of combinations
	++level;
	int combo_counter;
	for(int i = 1; i <= level; ++i) {
		combo_counter += i;
	}

	// compares circuits wires to desired outputs
	if(check_output(ex_list.front(), sum, c_out) == 0) {
		// adds NOT gate 
		add_not(not_counter);
		++not_counter;

		// adds AND/OR gate
		add_and(combo_counter);
		add_or(combo_counter);

		// remove "first" element
		ex_list.pop();

		search(sum, c_out);
	}
	else 
		return ex_list.front();
}