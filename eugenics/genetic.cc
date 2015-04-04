#include "genetic.h"

#include <string>
#include <sstream>
#include <iostream>
#include <utility>    // std::map
#include <algorithm>  // std::max
#include <random>     // std::mt19937

#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <ctime>  // std::time

#include "gate.h"
#include "genetic_circuit.h"
#include "utility.h"

Genetic::Genetic(int n, BooleanTable outputs) : Genetic(n, outputs, 1000) {}

Genetic::Genetic(int n, BooleanTable outputs, int population_size)
    : input_no(n),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()) {
  population = spawnPopulation(population_size);
}

Genetic::Genetic(int n, BooleanTable outputs, std::map<int, GeneticCircuit> pop)
    : population(pop),
      input_no(n),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()) {}

std::pair<GeneticCircuit, GeneticCircuit> Genetic::split(GeneticCircuit circuit,
                                                         int split_index) {
  // split gates
  std::vector<Gate *> lhs_gates(std::begin(circuit.getGates()),
                                std::begin(circuit.getGates()) + split_index);
  std::vector<Gate *> rhs_gates(std::begin(circuit.getGates()) + split_index,
                                std::end(circuit.getGates()));

  // split circuit and c2 into a and b at dist(rand_engine)
  GeneticCircuit c1a(circuit.getInputCount(), circuit.getOutputCount(),
                     lhs_gates);
  GeneticCircuit c1b(circuit.getInputCount(), circuit.getOutputCount(),
                     rhs_gates);

  return std::pair<GeneticCircuit, GeneticCircuit>(c1a, c1b);
}

GeneticCircuit Genetic::splice(GeneticCircuit circuit_lhs,
                               GeneticCircuit circuit_rhs) {}

std::pair<GeneticCircuit, GeneticCircuit> Genetic::splitAndSplice(
    GeneticCircuit circuit_1, GeneticCircuit circuit_2) {
  // random numbers should be in normal distribution
  std::uniform_int_distribution<> dist{input_no,
                                       (int)expected_outputs.front().size()};

  // first half size
  int split_index = dist(rand_engine);
}

std::map<int, GeneticCircuit> Genetic::spawnPopulation(int populationSize) {
  std::map<int, GeneticCircuit> spawned_pop;
  while (spawned_pop.size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    int circuit_fitness = c.generateFitness();
    c.setFitness(circuit_fitness);

    std::string errmsg =
        "Genetic::spawnPopulation inserting Circuit "
        "fitness: " +
        std::to_string(circuit_fitness);
    errlog(errmsg);

    std::pair<int, GeneticCircuit> zergling(c.hash_circ(), c);
    spawned_pop.insert(zergling);
    std::ostringstream errstream;
    errstream << "Genetic::spawnPopulation -- "
              << " --  " << spawned_pop.size();
    errlog(errstream.str(), SHOW_POPULATION_LOG);
  }
  return spawned_pop;
}
