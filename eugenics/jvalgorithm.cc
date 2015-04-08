#include <vector>
#include <queue>
#include <string>
#include <map>
#include <functional>
#include "jvalgorithm.h"
#include "utility.h"

using namespace std;

int level = 0;
Ckt_Algo::Ckt_Algo(Circuit circuit) : correct_circuit_output(), output_set(new vector<vector<vector<bool>>>)  {
  ex_list.push(circuit);
}
size_t hash_output(vector<vector<bool>> output){
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

bool Ckt_Algo::isUnique(Circuit candidate){
  bool need_more_possibilities = (candidate.getOutputCount() < 2);
  size_t hashed_val = hash_output(candidate.evaluateAllInputs());
  auto search = unique_map.find(hashed_val);
  if(search == unique_map.end()) { //if(hashed_val is unique)
    unique_map.insert(pair<size_t, int>(hashed_val, candidate.getNotCount()));
    return true;
  }
  else if(search->second > candidate.getNotCount()){
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

void Ckt_Algo::checkPermAndMap(Circuit* check, vector<vector<bool>> desired){
  return;
    vector<vector<bool>> actual = check->evaluateAllInputs();
    vector<vector<bool>> transposed_actual(actual.size());
    vector<vector<bool>> transposed_expected(actual.size());
    //transposes our vectors to work easily with columns later
      for (int i = 0; i < actual.size(); ++i) {
        for (int j = 0; j < actual.size(); ++j) {
          transposed_actual[i].push_back(actual[j][i]);
          transposed_expected[i].push_back(desired[j][i]);
        }
      }

      for (int i = 0; i < actual.size(); ++i) {
        for (int j = 0; j < actual.size(); ++j) {
          if(transposed_actual[i] == transposed_expected[j]){
            /* check->mapOutputToOutput(i, j); // */
            return;
          }
        }
      }


      /* bool is_working = true; */
      /* for (int i = 0; i < actual.size(); ++i) { */
      /*   for (int j = 0; j < actual.size(); ++j) { */
      /*     if(transposed_actual[i][j] != actual[j][i] || transposed_expected[i][j] != desired[j][i]){ */
      /*           is_working = false; */
      /*           exit(-1); */
      /*     } */
      /*   } */
      /* } */



      /* if(!is_equal_to_col){ */
      /*     is_equal_to_circuit = false; */
      /* } */
      /* else{ */
      /*   current_circ->mapGateToOutput(current_circ->getGateCount() - i - 1, i); */
      /* } */
      /* is_equal_to_col = false; */
    /* } */
}

//also maps correct gates to outputs
bool Ckt_Algo::circuitMatchesDesired(vector<vector<bool>> desired) {
    // check if output of current circuit equals desired
    Circuit * current_circ = &ex_list.front();

    //check permutations of output and map if equal
    checkPermAndMap(current_circ, desired);
    vector<vector<bool>> circ_output = current_circ->evaluateAllInputs();


    if(circ_output.size() != desired.size()){
      errlog("Getting a weird output size while checking correctness", true);
      return false;
    }
    for (int i = 0; i < circ_output.size(); ++i) {
      if (circ_output[i] != desired[i]) {
        return false;
      }
    }

    //if it got this far, circuit must be correct!
    correct_circuit_output = circ_output;
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
    if(isUnique(next)){
      ex_list.push(next);
    }
  }
}

void Ckt_Algo::addAnd(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = 0; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(AND, i, j);
      string errmsg = "Ckt_Algo::addAnd: " + to_string(next.getGateCount()) +
        " AND " + to_string(i) + " " + to_string(j);
      errlog(errmsg);
      if(isUnique(next)){
        ex_list.push(next);
      }
    }
  }

}

void Ckt_Algo::addOr(int counter) {
  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  // eliminate the combinations that were used
  // on previous levels
  /* for (int i = 0; i < counter - 1; ++i) { */
  /*   for (int j = i + 1; j < counter; ++j) { */
  /*     or_map[to_string(i)+ to_string(j)] = 1; */
  /*   } */
  /* } */
  for (int i = 0; i < counter - 1; ++i) {
    for (int j = i + 1; j < counter; ++j) {
      Circuit next = ex_list.front();
      next.addGate(OR, i, j);
      string errmsg = "Ckt_Algo::addOr: " + to_string(next.getGateCount()) +
        " OR " + to_string(i) + " " + to_string(j);
      errlog(errmsg);
      if(isUnique(next)){
        ex_list.push(next);
      }
    }
  }
}

vector<vector<bool>> Ckt_Algo::search(vector<vector<bool>> desired) {
  while (circuitMatchesDesired(desired) == false) {
    errlog("Ckt_Algo::search circuit did not match desired, search continuing");
    Circuit temp_c = ex_list.front();
    if(ex_list.empty()){
      errlog("Ckt_Algo::NO MORE QUEUE CIRCUITS");
      exit(-1);
    }
    // adds NOT/AND/OR gate
    /* errlog("Ckt_Algo::search addNot successful", true); */
    if(temp_c.getNotCount() < 2){
      addNot(temp_c.getGateCount());
    }
    if(temp_c.getGateCount()) {
      addAnd(temp_c.getGateCount());
      /* errlog("Ckt_Algo::search addAnd successful", true); */
      addOr(temp_c.getGateCount());
      /* errlog("Ckt_Algo::search addOr successful", true); */
    }
    errlog("Ckt_Algo::search found :" + to_string(unique_map.size()) + " unique circs ", true);
    errlog("Ckt_Algo::Queue still has :" + to_string(ex_list.size()) + " possibilities", true);

    // remove "first" element
    ex_list.pop();
    ++level;
  }
  errlog("Ckt_Algo::search found correct circuit!");
  return correct_circuit_output;
}
