#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>
#include "gate.h"
enum GateType { NOT, WIRE, OR, AND };
class Circuit {
 public:
  // DEPRECATED
  // inputs is a a row of the inputs portion of a truth table
  // output_no is the number of outputs desired
  Circuit(std::vector<bool> inputs, int output_no);

  // input_no is used to compute the input half of the truth table
  // e.g. input_no = 2 becomes:
  //// 00
  //// 01
  //// 10
  //// 11
  // output_no is the number of outputs desired
  Circuit(int input_no, int output_no);

  // number of gates
  int numGates() { return gates.size(); }

  // add a unary gate which takes the gate/wire at gates[index_1] as input
  int addGate(GateType gate_type, int index_1);
  // same as above, but with same syntax as text file representation
  // NOTE: output_index is checked if it is correct, not set to output_index
  int addGate(int output_index, GateType gate_type, int index_1);

  // add a binary gate which takes the gate/wire at gates[index_1]  and
  // gates[index_2] as input
  int addGate(GateType gate_type, int index_1, int index_2);
  // same as above, but with same syntax as text file representation
  // NOTE: output_index is checked if it is correct, not set to output_index
  int addGate(int output_index, GateType gate_type, int index_1, int index_2);

  // evaluate a circuit for all sets of inputs
  // e.g. the entire set of inputs for an XOR gate
  std::vector<std::vector<bool>> evaluateAllInputs();

  // evaluate a circuit for just one row of inputs
  // e.g. {false,false,true}
  std::vector<bool> evaluateInputSet(std::vector<bool> input_set);

  //
  /* std::vector<std::vector<bool> > evaluate(); */

  // generate all combinations of input_no number of inputs
  // e.g. if input_no is 3, returns 2^3 sets of input_no wide inputs
  std::vector<std::vector<bool>> generateInputSet();

 private:
  // gates and wires storage
  std::vector<Gate*> gates;

  // number of outputs
  int output_no;
  // number of inputs
  int input_no;

  //// Statistics
  void printStatistics();
  // number of And gates
  int and_no;
  // number of Or gates
  int or_no;
  // number of Not gates
  int not_no;
  // number of Wires
  int wire_no;
};

#endif
