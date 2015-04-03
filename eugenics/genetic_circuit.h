#ifndef GENETIC_CIRCUIT_H
#define GENETIC_CIRCUIT_H
#include "circuit.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class GeneticCircuit : public Circuit {
  /* Circuit::Circuit(int inputs, int o) : output_no(o), input_no(inputs) { */
  /*   // initialize statistics to 0 */
  /*   and_no = or_no = not_no = wire_no = 0; */
  /*   mapped_outputs = vector<int>(output_no, -1); */
  /*   // create initial input wires */
  /*   for (int i = 0; i < input_no; ++i) { */
  /*     wire_no++; */
  /*     std::string errmsg = "Circuit::Circuit: " +
   * std::to_string(getGateCount()) + */
  /*                          " WIRE " + std::to_string(i); */
  /*     errlog(errmsg); */

  /*     Gate* wire = new Wire(false, i); */
  /*     gates.push_back(wire); */
  /*   } */
  /* } */

 public:
  GeneticCircuit(int input_num, int output_num)
      : Circuit(input_num, output_num) {
    if (input_num < 2) {
      std::string errmsg = "Need more than 2 inputs to create gate";
      errlog(errmsg);
      exit(-1);
    }
    std::vector<GateType> gate;
    gate.push_back(NOT);
    gate.push_back(OR);
    gate.push_back(AND);

    int num_of_gates = rand() % 32;  // random number between 0 and 30
    for (int i = 0; i < num_of_gates; ++i) {
      // random number between 0 and 2
      GateType rand_gate = gate[rand() % 3];

      if (rand_gate == NOT) {
        addGate(rand_gate, getGateCount() - 1);
      } else if (rand_gate == OR || rand_gate == AND) {
        addGate(rand_gate, getGateCount() - 2, getGateCount() - 1);
      }
    }
  }

  void setFitness(int f) { fitness = f; }

 protected:
  int fitness;
};

#endif
