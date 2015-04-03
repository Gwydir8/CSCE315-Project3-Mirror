#ifndef GENETIC_CIRCUIT_H
#define GENETIC_CIRCUIT_H

#include <vector>

#include <cstdio>
#include <cstdlib>

#include "circuit.h"

class GeneticCircuit : public Circuit {
 public:
  GeneticCircuit(int input_num, int output_num);

  void setFitness(int f);

 private:
  int fitness;
};

#endif
