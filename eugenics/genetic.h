#ifndef GENETIC_H
#define GENETIC_H

#include "genetic_circuit.h"
#include <vector>
#include <map>
#include <utility>

#include "circuit.h"

class Genetic {
 public:
  Genetic() : population(), input_no(), expected_outputs(){};
  Genetic(int input_no, BooleanTable outputs);
  Genetic(int input_no, BooleanTable outputs, std::map<int, Circuit> pop);
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

};

#endif /* GENETIC_H */
