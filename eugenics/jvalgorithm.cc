#include <vector>
#include <queue>
#include "jvalgorithm.h"
#include "utility.h"

using namespace std;

Ckt_Algo::Ckt_Algo(Circuit circuit) : circ_output(), output_set(new std::vector<std::vector<std::vector<bool>>>)  {
  ex_list.push(circuit);
}

bool Ckt_Algo::circuitMatchesDesired(vector<vector<bool>> desired) {
  
  bool equal_to_vector = true;
  while(equal_to_vector == true) {
    equal_to_vector = false;
    // compare column of desired and column of current circuit
    /*ex_list.front().evaluateAllInputs();
    vector<vector<bool>> temp_eval = ex_list.front().getEval();
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
        errlog("Ckt_Algo::circuitMatchesDesired: col_desired == col_eval");
        ex_list.front().mapGateToOutput(ex_list.front().getGateCount() - 1, j);
    }*/
    ex_list.front().evaluateAllInputs();
    // check if output of current circuit equals desired
    circ_output = ex_list.front().getEval();
    if (desired == circ_output) {
      errlog("Ckt_Algo::circuitMatchesDesired: circ_output == desired");
      return true;
    } else {
      // check if output of current circuit is unique
      for (int i = 0; i < output_set->size(); ++i) {
        if (circ_output == (*output_set)[i]) {
          // it's a duplicate so don't put into vector
          std::string errmsg = "Ckt_Algo::circuitMatchesDesired: circ_output == output_set";
          errlog(errmsg);
          equal_to_vector = true;
          ex_list.pop();
          break;
        }
      }
      if (equal_to_vector == false) {
        std::string errmsg = "Ckt_Algo::circuitMatchesDesired: push_back(circ_output)";
        errlog(errmsg);
        // if output of current circuit is unique push into output_set
        output_set->push_back(circ_output);
      }
    }
  }
  std::string errmsg = "Ckt_Algo::circuitMatchesDesired: output_set->size()  = " +
                        std::to_string(output_set->size()) + " ex_list.size() = " +
                        std::to_string(ex_list.size());
  errlog(errmsg);
  return false;
}

void Ckt_Algo::addNot(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    std::string errmsg = "Ckt_Algo::addNot: " + std::to_string(next.getGateCount()) +
                         " NOT " + std::to_string(i);
    errlog(errmsg);
    ex_list.push(next);
  }
}

void Ckt_Algo::addAnd(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(AND, i, j);
      std::string errmsg = "Ckt_Algo::addAnd: " + std::to_string(next.getGateCount()) +
                           " AND " + std::to_string(i) + " " + std::to_string(j);
      errlog(errmsg);
      ex_list.push(next);
    }
  }
}

void Ckt_Algo::addOr(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(OR, i, j);
      std::string errmsg = "Ckt_Algo::addOr: " + std::to_string(next.getGateCount()) +
                           " OR " + std::to_string(i) + " " + std::to_string(j);
      errlog(errmsg);
      ex_list.push(next);
    }
  }
}

vector<vector<bool>> Ckt_Algo::search(vector<vector<bool>> desired) {
  while (circuitMatchesDesired(desired) == false) {
    errlog("Ckt_Algo::search circuit did not match desired, search continuing");

    // adds NOT/AND/OR gate
    addNot(ex_list.front().getGateCount());
    errlog("Ckt_Algo::search addNot successful");
    addAnd(ex_list.front().getGateCount());
    errlog("Ckt_Algo::search addNot successful");
    addOr(ex_list.front().getGateCount());
    errlog("Ckt_Algo::search addNot successful");

    // remove "first" element
    ex_list.pop();
  } 
  errlog("Ckt_Algo::search found correct circuit!");
  return circ_output;
}
