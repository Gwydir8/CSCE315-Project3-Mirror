#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>
#include "gate.h"
enum GateType { NOT, WIRE, OR, AND };
class Circuit {
 private:
  int output_no;
  int input_no;
  std::vector<Gate*> gates;

 public:
  Circuit(std::vector<bool> vec, int output_no);
  Circuit(int input_no, int output_no);

  int numGates() { return gates.size(); }

  int addGate(GateType gate_type, int index_1);
  int addGate(GateType gate_type, int index_1, int index_2);
  std::vector<std::vector<bool>> evaluateAllInputs();
  std::vector<bool> evaluateInputSet(std::vector<bool> input_set);
  /* std::vector<std::vector<bool> > evaluate(); */
  std::vector<std::vector<bool>> getPossibleInputs();
};

#endif
