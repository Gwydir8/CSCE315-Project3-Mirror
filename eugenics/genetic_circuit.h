#ifndef GENETIC_CIRCUIT_H
#define GENETIC_CIRCUIT_H

#include <vector>
#include <random>
#include "circuit.h"

class GeneticCircuit : public Circuit {
 public:
  GeneticCircuit(int input_num, int output_num, std::mt19937* rand_eng);

  void setFitness(int f);

 protected:
  std::uniform_int_distribution<> gate_dist{0, 2};
  std::uniform_int_distribution<> number_dist{0, 40};
  std::mt19937* rand_engine;
  int fitness;
};

#endif
