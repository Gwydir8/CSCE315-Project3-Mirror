#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <map>
#include <utility>

#include "circuit.h"

class Genetic {
 public:
  Genetic();
  virtual ~Genetic();

  void fitness();

  void spliceCircuit();
  void splitCircuit();

  void splitAndSplice();

 private:
  std::map<int, Circuit> population;

  BooleanTable expected_inputs;
  BooleanTable expected_outputs;

  void spawnPopulation(int populationSize);
};

#endif /* GENETIC_H */
