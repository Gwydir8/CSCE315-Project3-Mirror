#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <map>
#include <utility>
#include <random>     // std::mt19937
#include <algorithm>  // std::max
#include <cstddef>    //std::size_t

#include "genetic_circuit.h"

class Genetic {
 public:
  Genetic() : population(), input_no(), expected_outputs() {}
  Genetic(int n, BooleanTable outputs) : Genetic(n, outputs, 1000) {}
  Genetic(int input_no, BooleanTable expect_outputs, int population_size);
  Genetic(int input_no, BooleanTable expect_outputs,
          std::map<std::size_t, GeneticCircuit> pop);
  // ~Genetic() { std::cerr << "~Genetic" << std::endl; }

  // "cut" two circuits at random point
  std::pair<std::vector<Gate *>, std::vector<Gate *>> split(
      GeneticCircuit circuit, int split_index);

  // splice together c1a and c2b, and c2a and c1b
  GeneticCircuit splice(std::vector<Gate *> base_part,
                        std::vector<Gate *> appended_part);

  // perform split and splice in one function
  std::pair<GeneticCircuit, GeneticCircuit> splitAndSplice(
      GeneticCircuit circuit_1, GeneticCircuit circuit_2);

  int getExpectedInputs() const { return input_no; }
  BooleanTable getExpectedOutputs() const { return expected_outputs; }
  std::map<std::size_t, GeneticCircuit> getPopulation() const { return population; }

  std::map<std::size_t, GeneticCircuit> spawnPopulation(std::size_t populationSize);

  int generateFitness(GeneticCircuit c);
 private:
  std::map<std::size_t, GeneticCircuit> population;

  int input_no;
  BooleanTable expected_outputs;

  std::minstd_rand rand_engine;
};

#endif /* GENETIC_H */
