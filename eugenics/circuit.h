#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>
#include "gate.h"

typedef std::vector<std::vector<bool>> BooleanTable;

enum GateType { NOT, WIRE, OR, AND };
class Circuit {
 public:
  // Constructor
  // input_no is used to compute the input half of the truth table
  // e.g. input_no = 2 becomes:
  //// 00
  //// 01
  //// 10
  //// 11
  // output_no is the number of outputs desired
  Circuit(int input_no, int output_no);
  // virtual ~Circuit();

  int getOutputCount() const { return output_no; }
  int getInputCount() const { return input_no; }
  int getAndCount() const { return and_no; }
  int getOrCount() const { return or_no; }
  int getNotCount() const { return not_no; }
  int getWireCount() const { return wire_no; }
  int getGateCount() const { return gates.size(); }

  // gate_index := which gate we want to always have as ouput
  // desired_output_index := which output to map it to
  void mapGateToOutput(int gate_index, int desired_output_index);

  // Valid Gate types with 1 input { NOT, WIRE}
  // add a unary gate which takes the gate/wire at gates[index_1] as input
  int addGate(GateType gate_type, int index_1);

  // Valid Gate types with 2 input { OR, AND}
  // add a binary gate which takes the gate/wire at gates[index_1]  and
  // gates[index_2] as input
  int addGate(GateType gate_type, int index_1, int index_2);

  // evaluate a circuit for all sets of inputs
  // e.g. the entire set of inputs for an XOR gate
  BooleanTable evaluateAllInputs();

  // evaluate a circuit for just one row of inputs
  // e.g. {false,false,true}
  std::vector<bool> evaluateInputSet(std::vector<bool> input_set);

  // generate all combinations of input_no number of inputs
  // e.g. if input_no is 3, returns 2^3 sets of input_no wide inputs
  BooleanTable generateInputSet();

  /*---end of usefulness for algorithm folks----*/
  // DEPRECATED Constructor
  // inputs is a a row of the inputs portion of a truth table
  // output_no is the number of outputs desired
  Circuit(std::vector<bool> inputs, int output_no);

  // same as above, but with same syntax as text file representation
  // NOTE: output_index is checked if it is correct, not set to output_index
  int addGate(int output_index, GateType gate_type, int index_1, int index_2);

  // same as above, but with same syntax as text file representation
  // NOTE: output_index is checked if it is correct, not set to output_index
  int addGate(int output_index, GateType gate_type, int index_1);

  // Manual Constructor, Sets everything
  Circuit(int input_no, int output_no, std::vector<Gate *> gates);

  // return gates
  std::vector<Gate *> getGates() { return gates; }
  void setGates(std::vector<Gate *> gates_) { gates = gates_; }

  // friend std::istream& operator>>(std::istream& is, Circuit& circuit);

  friend std::ostream &operator<<(std::ostream &os, const Circuit &circuit);

  void writeCircuitToFile() const;

  // print stats
  void printStatistics();

 private:
  // gates and wires storage
  std::vector<Gate *> gates;
  std::vector<int> mapped_outputs;
  // number of outputs
  int output_no;
  // number of inputs
  int input_no;

  //// Statistics
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
