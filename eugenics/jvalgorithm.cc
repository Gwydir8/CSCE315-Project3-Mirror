#include <vector>
#include <queue>
#include "jvalgorithm.h"
#include "utility.h"

using namespace std;

Ckt_Algo::Ckt_Algo(Circuit circuit) : circ_output(), output_set(new std::vector<std::vector<std::vector<bool>>>)  {
  ex_list.push(circuit);
}

bool Ckt_Algo::circuit_matches_desired(vector<vector<bool>> desired) {
  
  bool equal_to_vector = true;
  while(equal_to_vector == true) {
    equal_to_vector = false;
    /*ex_list.front().evaluateAllInputs();
    vector<vector<bool>> temp_eval = ex_list.front().get_eval();
    for(int j = 0; j < desired[0].size(); ++j) {
      vector<bool> col_desired;
      vector<bool> col_eval;
      for(int i = 0; i < desired.size(); ++i) {
        col_desired.push_back(desired[i][j]);
      }
      for(int i = 0; i < temp_eval.size(); ++i) {
        col_eval.push_back(temp_eval[i][j]);
      } 
      if(col_desired == col_eval)
        ex_list.front().mapGateToOutput(ex_list.front().getGateCount() - 1, j);
    }*/
    ex_list.front().evaluateAllInputs();

    circ_output = ex_list.front().get_eval();
    if (desired == circ_output) {
      return true;
    } else {
      for (int i = 0; i < output_set->size(); ++i) {
        if (circ_output == (*output_set)[i]) {
          // it's a duplicate so don't put into vector
          equal_to_vector = true;
          ex_list.pop();
          break;
        }
      }
      if (equal_to_vector == false) {
        output_set->push_back(circ_output);
      }
    }
  }
  return false;
}

void Ckt_Algo::add_not(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    ex_list.push(next);
  }
}

void Ckt_Algo::add_and(int counter) {
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

void Ckt_Algo::add_or(int counter) {
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

vector<vector<bool>> Ckt_Algo::search(vector<vector<bool>> desired) {
  // somehow use mapoutput function
  while (circuit_matches_desired(desired) == false) {
    errlog("Ckt_Algo::search circuit did not match desired, search continuing");

    // adds NOT/AND/OR gate
    add_not(ex_list.front().getGateCount());
    add_and(ex_list.front().getGateCount());
    add_or(ex_list.front().getGateCount());

    // remove "first" element
    ex_list.pop();

  } 
  errlog("Ckt_Algo::search found correct circuit!");
  return circ_output;
}
