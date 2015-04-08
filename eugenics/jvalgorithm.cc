#include <vector>
#include <queue>
#include <string>
#include <map>
#include <functional>
#include "jvalgorithm.h"
#include "utility.h"

using namespace std;

Ckt_Algo::Ckt_Algo(Circuit circuit)
    : correct_circuit_output(),
      correct_circuit(circuit),
      output_set(new vector<vector<vector<bool>>>) {
  ex_list.push(circuit);
}
size_t hash_output(vector<vector<bool>> output) {
  string s = "";
  for (vector<bool> row : output) {
    for (bool bit : row) {
      s += to_string((int)bit);
    }
  }
  hash<string> hash_fn;
  size_t hash = hash_fn(s);
  return hash;
}

bool Ckt_Algo::isUnique(Circuit candidate) {
  // bool need_more_possibilities = (candidate.getOutputCount() < 2);
  size_t hashed_val = hash_output(candidate.evaluateAllInputs());
  auto search = unique_map.find(hashed_val);
  if (search == unique_map.end()) {  // if(hashed_val is unique)
    unique_map.insert(pair<size_t, int>(hashed_val, candidate.getNotCount()));
    return true;
  } else if (search->second > candidate.getNotCount()) {
    search->second = candidate.getNotCount();
    return true;
  }
  /* else if(need_more_possibilities){ */
  /*   if(ex_list.size() < 10){ */
  /*       return true; */
  /*   } */
  /* } */
  return false;
}

// also maps correct gates to outputs
bool Ckt_Algo::circuitMatchesDesired(vector<vector<bool>> desired) {
  // check if output of current circuit equals desired
  Circuit* current_circ = &ex_list.front();

  // check permutations of output and map if equal
  /* checkPermAndMap(current_circ, desired); */
  vector<vector<bool>> circ_output = current_circ->evaluateAllInputs();

  if (circ_output.size() != desired.size()) {
    errlog("Getting a weird output size while checking correctness");
    return false;
  }

  for (std::size_t i = 0; i < circ_output.size(); ++i) {
    if (circ_output[i] != desired[i]) {
      return false;
    }
  }

  // if it got this far, circuit must be correct!
  correct_circuit_output = circ_output;
  correct_circuit = *current_circ;
  return true;
}

void Ckt_Algo::addNot(int counter) {
  // only add a not gate to the end of the circuit

  for (int i = 0; i < counter - 1; ++i) {
    Circuit next = ex_list.front();
    next.addGate(NOT, i);
    string errmsg = "Ckt_Algo::addNot: " + to_string(next.getGateCount()) +
                    " NOT " + to_string(counter);
    errlog(errmsg);
    if (isUnique(next)) {
      ex_list.push(next);
    }
  }
}

void Ckt_Algo::addAnd(int counter) {
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i; j < counter - 1; ++j) {
      Circuit next = ex_list.front();
      next.addGate(AND, i, j);
      string errmsg = "Ckt_Algo::addAnd: " + to_string(next.getGateCount()) +
                      " AND " + to_string(i) + " " + to_string(j);
      errlog(errmsg);
      if (isUnique(next)) {
        ex_list.push(next);
      }
    }
  }
}

void Ckt_Algo::addOr(int counter) {
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(OR, i, j);
      string errmsg = "Ckt_Algo::addOr: " + to_string(next.getGateCount()) +
                      " OR " + to_string(i) + " " + to_string(j);
      errlog(errmsg);
      if (isUnique(next)) {
        ex_list.push(next);
      }
    }
  }
}

vector<vector<bool>> Ckt_Algo::search(vector<vector<bool>> desired) {
  while (circuitMatchesDesired(desired) == false) {
    errlog("Ckt_Algo::search circuit did not match desired, search continuing");
    Circuit temp_c = ex_list.front();
    if (ex_list.empty()) {
      errlog("Ckt_Algo::NO MORE QUEUE CIRCUITS");
      exit(-1);
    }
    int gate_count = temp_c.getGateCount();
    // adds NOT/AND/OR gate
    /* errlog("Ckt_Algo::search addNot successful", true); */
    if (temp_c.getNotCount() < 2) {
      addNot(gate_count);
    }
    if (temp_c.getGateCount()) {
      addAnd(gate_count);
      /* errlog("Ckt_Algo::search addAnd successful", true); */
      addOr(gate_count);
      /* errlog("Ckt_Algo::search addOr successful"); */
    }
    errlog("Ckt_Algo::search found :" + to_string(unique_map.size()) +
           " unique circs ");
    errlog("Ckt_Algo::Queue still has :" + to_string(ex_list.size()) +
           " possibilities");
    errlog("Ckt_Algo::On Level Number::" + to_string(gate_count) + " ");

    // remove "first" element
    ex_list.pop();
  }
  errlog("Ckt_Algo::search found correct circuit!");
  return correct_circuit_output;
}
