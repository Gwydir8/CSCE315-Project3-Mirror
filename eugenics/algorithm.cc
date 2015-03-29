#include <vector>
#include <queue>
#include "algorithm.h"
using namespace std;


Algo::Algo() {
  // initalize base circuit into exhaustive list
  Circuit base(3,2);
  ex_list.push(base);
}

int Algo::check_output(Circuit x, vector<vector<bool>> desired) {
  // generates an output set based on the circuit
  vector<vector<bool>> output_set = x.evaluateAllInputs();
  
  // compares output set of current circuit and desired
  // make sure generated set and desired are same size
  // and NOT gates are less then or equal to 2
  if (output_set.size() == desired.size() && x.getNotCount() <= 2) {
	for (int i = 0; i < desired.size(); ++i) {
		for (int j = 0; j < desired[i].size(); ++j) {
		  // if generated output set equals desired output
		  if (output_set[i][j] == desired[i][j]);
		  // if generated output set doesn't equal desired output
		  else
			return 0;
		}
	}
  }
  else 
    return 0;

  // sets generated output set to global set
  circ_output = output_set;
  return 1;
}

void Algo::add_not(int counter) {
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    ex_list.push(next);
  }
}

void Algo::add_and(int counter) {
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(AND, i);
    ex_list.push(next);
  }
}

void Algo::add_or(int counter) {
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(OR, i);
    ex_list.push(next);
  }
}

vector<vector<bool>> Algo::search(vector<vector<bool>> desired) {

  // keeps track of # of combinations
  ++level;
  int combo_counter=0;
  for (int i = 1; i <= level; ++i) {
    combo_counter += i;
  }

  // compares circuits wires to desired outputs
  if (check_output(ex_list.front(), desired) == 0) {
    // adds NOT gate
	if(not_counter < 2){
		add_not(not_counter);
		++not_counter;
	}
    // adds AND/OR gate
    add_and(combo_counter);
    add_or(combo_counter);

    // remove "first" element
    ex_list.pop();

    search(desired);
  } 
  else {
    return circ_output;
  }
}
