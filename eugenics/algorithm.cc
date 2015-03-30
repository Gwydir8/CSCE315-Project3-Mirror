#include <vector>
#include <queue>

#include "algorithm.h"
#include "utility.h"

using namespace std;

Algo::Algo() : circ_output() {
  // initalize base circuit into exhaustive list
  Circuit base(3, 2);
  ex_list.push(base);
}

Algo::Algo(Circuit circuit) : circ_output() { ex_list.push(circuit); }

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
        if (output_set[i][j] == desired[i][j])
          ;
        // if generated output set doesn't equal desired output
        else
          return 0;
      }
    }
  } else
    return 0;

  // sets generated output set to global set
  circ_output = output_set;
  return 1;
}

void Algo::add_not(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    ex_list.push(next);
  }
}

void Algo::add_and(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(AND, i, j);
      ex_list.push(next);
    }
  }
}

void Algo::add_or(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(OR, i, j);
      ex_list.push(next);
    }
  }
}

vector<vector<bool>> Algo::search(vector<vector<bool>> desired) {
  // compares circuits wires to desired outputs
  if (check_output(ex_list.front(), desired) == 0) {
    // adds NOT/AND/OR gate
    add_not(ex_list.front().getGateCount());
    add_and(ex_list.front().getGateCount());
    add_or(ex_list.front().getGateCount());

    // remove "first" element
    ex_list.pop();

    // search the next circuit
    search(desired);
  } else {
    return circ_output;
  }
}
