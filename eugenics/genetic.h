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

  // "cut" two circuits at random point
  void split(Circuit c1, Circuit c2);
  // splice together c1a and c2b, and c2a and c1b
  void splice();

  // perform split and splice in one function
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
