#include "traditional_algorithm.h"
using namespace std;
Circuit Circuit::search() {
  queue<Circuit> Q;
  // remove "first" element
  q.push(root);
  while(Q.empty() == false) {
    Circuit current = Q.pop();
    for(Circuit circuit_to_check : allPossibleCircuits(v)){
      if(true) { //if v is "undiscovered"
        Q.push(circuit_to_check);
      }
      if (isCorrectCircuit(current)){
        return Circuit;
      }
    }
  }
  bool Circuit::isCorrectCircuit(Circuit c){
    if(evaluateAllInputs() == expected_output)
      return true;
    else
      return false;
  }


  vector<bool> init = {0, 0, 0};

  int level = 1;
  /* ex_list.push(base); */
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


  search();
}
bool checkPermutation(){ //check if one of the outputs matches one of the expected...
  return true;
}
bool keepPermutation(){

  return true;
}
