#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <map>
#include <utility>
#include <random>     // std::mt19937
#include <algorithm>  // std::max

#include "genetic_circuit.h"
#include "circuit.h"


// 2^((2^3)*2)
// 2^
class Genetic {
 public:
  Genetic() : population(), expected_inputs(), expected_outputs(){};
  Genetic(BooleanTable inputs, BooleanTable outputs)
      : population(),
        expected_inputs(inputs),
        expected_outputs(outputs),
        rand_engine(std::random_device{}()),
        dist(inputs.front().size(), outputs.front().size()) {
    spawnPopulation(1000);
  };
  virtual ~Genetic();

  int fitness(GeneticCircuit c);

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

  // mersenne_twister_engine(mt19937)
  std::mt19937 rand_engine;
  // random numbers should be in normal distribution
  std::uniform_int_distribution<> dist;
};

size_t hash_circ(GeneticCircuit c);

#endif /* GENETIC_H */
