#include <vector>
#include <queue>
#include "circuit.h"

// initalize base circuit into exhaustive list
queue<Circuit> ex_list;
vector<bool> init = {0, 0, 0}
Circuit base (init, 0);
ex_list.push(base);

int level = 1;

void search() {

	// keeps track of # of combinations
	++level;
	int combo_counter;
	for(int i = 1; i <= level; ++i) {
		other_counter += i;
	}

	// adds NOT gate 
	for(int i = 0; i < not_counter; ++i) {
		Circuit next = ex_list.front();
		next.addGate(NOT, i);
		ex_list.push(next);
	}
	++not_counter;

	// adds AND/OR gate
	for(int i = 0; i < combo_counter; ++i) {
		Circuit next = ex_list.front();
		next.addGate(AND, i);
		ex_list.push(next);
	}
	for(int i = 0; i < combo_counter; ++i) {
		Circuit next = ex_list.front();
		next.addGate(OR, i);
		ex_list.push(next);
	}

	// remove "first" element
	ex_list.pop();

	search();
}