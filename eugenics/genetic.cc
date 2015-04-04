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

GeneticCircuit Genetic::splice(Circuit base_part, Circuit appended_part) {
  std::vector<Gate> combined_gates = base_part.getGates();
  std::vector<Gate> a = appended_part.getGates();

  combined_gates.reserve(combined_gates.size() + a.size());
  combined_gates.insert(combined_gates.end(), a.begin(), a.end());

  GeneticCircuit new_circuit(input_no, expected_outputs.size(), combined_gates);
  return new_circuit;
}

std::pair<GeneticCircuit, GeneticCircuit> Genetic::splitAndSplice(GeneticCircuit c_1, GeneticCircuit c_2){
  std::pair<GeneticCircuit, GeneticCircuit> swapped_circuits(c_1, c_2);

  //Generate random index to split at
  int limiting_index = (c_1.getGateCount() < c_2.getGateCount())? c_1.getGateCount() : c_2.getGateCount();
  std::uniform_int_distribution<> dist{input_no, limiting_index - 1};
  int split_index = dist(rand_engine);

  std::pair<GeneticCircuit, GeneticCircuit> c_1_halves = split(c_1, split_index);
  std::pair<GeneticCircuit, GeneticCircuit> c_2_halves = split(c_2, split_index);

  swapped_circuits.first = splice(c_1_halves.first, c_2_halves.second);
  swapped_circuits.second = splice(c_2_halves.first, c_1_halves.second);

  return swapped_circuits;
}


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
