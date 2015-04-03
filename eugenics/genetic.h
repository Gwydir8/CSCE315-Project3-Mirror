#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <map>
#include <utility>

#include "circuit.h"

class Genetic {
 public:
  Genetic() : population(), expected_inputs(), expected_outputs(){};
  Genetic(BooleanTable inputs, BooleanTable outputs)
      : population(), expected_inputs(inputs), expected_outputs(outputs) {
    spawnPopulation(1000);
  };
  virtual ~Genetic();

  int fitness(Circuit c);

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
