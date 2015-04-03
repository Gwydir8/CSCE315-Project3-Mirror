#ifndef GENETIC_CIRCUIT_H
#define GENETIC_CIRCUIT_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "circuit.h"

class GeneticCircuit : public Circuit {
 public:

  GeneticCircuit(int input_num, int output_num, std::mt19937* rand_eng)
      : Circuit(input_num, output_num), rand_engine(rand_eng), fitness(0){
    if (input_num < 2) {
      std::string errmsg = "Need more than 2 inputs to create gate";
      errlog(errmsg);
      std::exit(EXIT_FAILURE);
    }
    std::vector<GateType> gate;
    gate.push_back(NOT);
    gate.push_back(OR);
    gate.push_back(AND);

    int num_of_gates = number_dist(*rand_engine);  // random number between 0 and 30
    for (int i = 0; i < num_of_gates; ++i) {
      // random number between 0 and 2
      GateType rand_gate = gate[gate_dist(*rand_engine)];

      if (rand_gate == NOT) {
        addGate(rand_gate, number_dist(*rand_engine) % getGateCount() );
      } else if (rand_gate == OR || rand_gate == AND) {

        addGate(rand_gate, number_dist(*rand_engine) % getGateCount(), number_dist(*rand_engine) % getGateCount());
      }
    }
  }

  void setFitness(int f) { fitness = f; }

 protected:
  std::uniform_int_distribution<> gate_dist{0, 2};
  std::uniform_int_distribution<> number_dist{0, 40};
  std::mt19937* rand_engine;
  int fitness;
};

#endif
