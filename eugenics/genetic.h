#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <map>
#include <utility>

#include "circuit.h"

class Genetic {
 public:
  Genetic(): expected_inputs(0), expected_outputs(0), population(){};
  Genetic(BooleanTable inputs, BooleanTable outputs): expected_inputs(0), expected_outputs(0), population(){};
  virtual ~Genetic();

  int fitness();

  void splice();
  void split();
  void splitAndSplice();

  BooleanTable getExpectedInputs() const { return expected_inputs; }
  BooleanTable getExpectedOutputs() const { return expected_outputs; }
  std::map<int, Circuit> getPopulation() const { return population; }


 private:
  std::map<int, Circuit> population;

  BooleanTable expected_inputs;
  BooleanTable expected_outputs;

  void spawnPopulation(int populationSize);
};

#endif /* GENETIC_H */