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
  Genetic() : population(), input_no(), expected_outputs(){};
  Genetic(int num_inputs, BooleanTable outputs)
      : population(),
        input_no(num_inputs),
        expected_outputs(outputs),
        rand_engine(std::random_device{}()) {
    spawnPopulation(1000);
  }
  Genetic(int num_inputs, BooleanTable outputs, std::map<int, Circuit> pop)
      : population(pop), input_no(num_inputs), expected_outputs(outputs) {}
  virtual ~Genetic();

  int fitness(GeneticCircuit c);

  // "cut" two circuits at random point
  void split(Circuit c1, Circuit c2);
  // splice together c1a and c2b, and c2a and c1b
  void splice();

  // perform split and splice in one function
  void splitAndSplice();

  int getExpectedInputs() const { return input_no; }
  BooleanTable getExpectedOutputs() const { return expected_outputs; }
  std::map<int, Circuit> getPopulation() const { return population; }
  std::map<int, Circuit> spawnPopulation(int populationSize);

 private:
  std::map<int, Circuit> population;

  int input_no;
  BooleanTable expected_outputs;

  // mersenne_twister_engine(mt19937)
  std::mt19937 rand_engine;
};

size_t hash_circ(GeneticCircuit c);

#endif /* GENETIC_H */
