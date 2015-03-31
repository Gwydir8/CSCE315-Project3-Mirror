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

bool Algo::circuit_matches_desired(Circuit x, vector<vector<bool>> desired) {
  // generates an output set based on the circuit
  vector<vector<bool>> output_set = x.evaluateAllInputs();

  // compares output set of current circuit and desired
  // make sure generated set and desired are same size
  // and NOT gates are less then or equal to 2
  if (desired == output_set) {
    errlog("Algo::Algo circuit output == desired output");
    // sets generated output set to global set
    circ_output = output_set;
    return true;
  } else {
    errlog("Algo::Algo circuit output != desired output");
    return false;
  }
}

void Algo::add_not(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    ex_list.push(next);
    std::string errmsg = "Algo::add_not [" + std::to_string(i) + "] = " +
                         std::to_string(next.getGateCount()) + " NOT " +
                         std::to_string(i);
    errlog(errmsg);
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
      std::string errmsg = "Algo::add_and [" + std::to_string(i) + "][" +
                           std::to_string(j) + "] = " +
                           std::to_string(next.getGateCount()) + " AND " +
                           std::to_string(i) + " " + std::to_string(j);
      errlog(errmsg);
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
      std::string errmsg = "Algo::add_or [" + std::to_string(i) + "][" +
                           std::to_string(j) + "] = " +
                           std::to_string(next.getGateCount()) + " OR " +
                           std::to_string(i) + " " + std::to_string(j);
      errlog(errmsg);
    }
  }
}

vector<vector<bool>> Algo::search(vector<vector<bool>> desired) {
  // compares circuits wires to desired outputs
  if (!circuit_matches_desired(ex_list.front(), desired)) {
    errlog("Algo::search circuit did not match desired, search continuing");

    // adds NOT/AND/OR gate
    add_not(ex_list.front().getGateCount());
    add_and(ex_list.front().getGateCount());
    add_or(ex_list.front().getGateCount());

    // remove "first" element
    ex_list.pop();

    // search the next circuit
    search(desired);

  } else {
    errlog("Algo::search found correct circuit!");
    return circ_output;
  }
}
