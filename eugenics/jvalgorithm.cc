#include <vector>
#include "jvalgorithm.h"
#include "utility.h"

using namespace std;

Ckt_Algo::Ckt_Algo(Circuit circuit) : circ_output() {
  circuit.evaluateAllInputs();
  ex_list.push_back(circuit);
}

bool Ckt_Algo::circuit_matches_desired(vector<vector<bool>> desired) {
  
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
  }
  

  // generates an output set based on the circuit
  circ_output = ex_list.front().evaluateAllInputs();

  // compares output set of current circuit and desired
  // make sure generated set and desired are same size
  // and NOT gates are less then or equal to 2
  if (desired == circ_output) {
    errlog("Ckt_Algo::Ckt_Algo circuit output == desired output");
    // sets generated output set to global set
    return true;
  } else {
    errlog("Ckt_Algo::Ckt_Algo circuit output != desired output");
    return false;
  }
}

void Ckt_Algo::add_not(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    next.evaluateAllInputs();
    // check if next circuit is equal to a circuit in vector
    bool equal_to_vector = false;
    if(next.getNotCount() < 3) {
      for (int j = 0; j < ex_list.size(); ++j) {
        if (next.get_eval() == ex_list[j].get_eval()) {
          // it's a duplicate so don't put into vector
          equal_to_vector = true;
          break;
        }
      }
      if (equal_to_vector == false) {
        ex_list.push_back(next);
        std::string errmsg = "Ckt_Algo::add_not [" + std::to_string(i) + "] = " +
                             std::to_string(next.getGateCount()) + " NOT " +
                             std::to_string(i);
        errlog(errmsg);
      }
    }
  }
}

void Ckt_Algo::add_and(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(AND, i, j);
      next.evaluateAllInputs();
      // check if next circuit is equal to a circuit in vector
      bool equal_to_vector = false;
      if(next.getNotCount() < 3) {
        for (int k = 0; k < ex_list.size(); ++k) {
          if (next.get_eval() == ex_list[k].get_eval()) {
            // it's a duplicate so don't put into vector
            equal_to_vector = true;
            break;
          }
        }
        if (equal_to_vector == false) {
          ex_list.push_back(next);
          std::string errmsg = "Ckt_Algo::add_and [" + std::to_string(i) + "][" +
                               std::to_string(j) + "] = " +
                               std::to_string(next.getGateCount()) + " AND " +
                               std::to_string(i) + " " + std::to_string(j);
          errlog(errmsg);
        }
      }
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
      next.evaluateAllInputs();
      // check if next circuit is equal to a circuit in vector
      bool equal_to_vector = false;
      if(next.getNotCount() < 3) {
        for (int k = 0; k < ex_list.size(); ++k) {
          if (next.get_eval() == ex_list[k].get_eval()) {
            // it's a duplicate so don't put into vector
            equal_to_vector = true;
            break;
          }
        }
        if (equal_to_vector == false) {
          ex_list.push_back(next);
          std::string errmsg = "Ckt_Algo::add_or [" + std::to_string(i) + "][" +
                               std::to_string(j) + "] = " +
                               std::to_string(next.getGateCount()) + " OR " +
                               std::to_string(i) + " " + std::to_string(j);
          errlog(errmsg);
        }
      }
    }
  }
}

vector<vector<bool>> Ckt_Algo::search(vector<vector<bool>> desired) {
  // compares circuits wires to desired outputs

  // somehow use mapoutput function
  while (circuit_matches_desired(desired) == false) {
    errlog("Ckt_Algo::search circuit did not match desired, search continuing");

    // adds NOT/AND/OR gate
    add_not(ex_list.front().getGateCount());
    add_and(ex_list.front().getGateCount());
    add_or(ex_list.front().getGateCount());

    // remove "first" element
    ex_list.erase(ex_list.begin());

    // search the next circuit
    // search(desired);

  }  // else {
  errlog("Ckt_Algo::search found correct circuit!");
  return circ_output;
  //}
}
