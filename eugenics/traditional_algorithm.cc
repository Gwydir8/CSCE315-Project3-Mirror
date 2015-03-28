#include "traditional_algorithm.h"
using namespace std;
Circuit TraditionalAlgorithm::search() {
  queue<Circuit> Q;
  // remove "first" element
  Q.push(root);
  while(Q.empty() == false) {
    Circuit current = Q.front();
    Q.pop();
    //checks single correct output
    if (isCorrectCircuit(current)){
      return current;
    }
    for(Circuit circuit_to_check : allPossibleCircuits(current)){
      Q.push(circuit_to_check);
    }
  }
}
}

vector<Circuit> TraditionalAlgorithm::allPossibleCircuits(Circuit c){
  vector<Circuit> all_possibilities;
  int output_gate_offset = getGateCount() - getOutputCount();
  for(int i = 0; i < c.getOutputCount(); ++i){
    //try a NOT
    Circuit added_not = c;
    added_not.addGate(NOT, output_gate_offset + i);//needs to add to the end...
    all_possibilities.push_back(added_not);
    //on odd nums, use binary gates, always can try a unary
    if(i % 2 == 1){
      //try AND
      Circuit added_and = c;
      added_and.addGate(AND, output_gate_offset + i-1, output_gate_offset + i);//needs to add to the end...
      all_possibilities.push_back(added_and);
      //try OR
      Circuit added_or = c;
      added_or.addGate(OR, output_gate_offset + i-1, output_gate_offset + i);//needs to add to the end...
      all_possibilities.push_back(added_or);
    }
  }
  return all_possibilities;
}

bool TraditionalAlgorithm::isCorrectCircuit(Circuit c){
  if(c.evaluateAllInputs() == expected_output)
    return true;
  else
    return false;
}

/* bool checkPermutation(){ //check if one of the outputs matches one of the expected... */
/*   return true; */
/* } */
/* bool keepPermutation(){ */

/*   return true; */
/* } */
