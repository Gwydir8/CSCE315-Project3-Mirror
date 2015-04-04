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
  std::cout << "Past Here a0" << std::endl;

  std::vector<Gate *> a = circuit.getGates();
  std::cout << a.size() << "  " << split_index << std::endl;
  std::vector<Gate *> lhs_gates(a.begin(),
                                a.begin() + split_index);
  std::cout << "Past Here a1" << std::endl;
  std::vector<Gate *> rhs_gates(a.begin() + split_index,
                                a.end());
  std::cout << "Past Here a2" << std::endl;

  // split circuit and c2 into a and b at dist(rand_engine)
  GeneticCircuit c1a(circuit.getInputCount(), circuit.getOutputCount(), &rand_engine,
                     lhs_gates);
  std::cout << "Past Here a3" << std::endl;
  GeneticCircuit c1b(circuit.getInputCount(), circuit.getOutputCount(), &rand_engine,
                     rhs_gates);
  std::cout << "Past Here a4" << std::endl;

  std::pair<GeneticCircuit, GeneticCircuit> split_pair(c1a, c1b);
  return split_pair;
}

GeneticCircuit Genetic::splice(Circuit base_part, Circuit appended_part) {
  std::vector<Gate *> combined_gates = base_part.getGates();
  std::vector<Gate *> a = appended_part.getGates();

  combined_gates.insert(std::end(combined_gates), std::begin(a), std::end(a));

  GeneticCircuit new_circuit(input_no, expected_outputs.front().size(), &rand_engine, combined_gates);
  return new_circuit;
}

std::pair<GeneticCircuit, GeneticCircuit> Genetic::splitAndSplice(
    GeneticCircuit c_1, GeneticCircuit c_2) {
  std::cout << "Past Here 1" << std::endl;
  std::pair<GeneticCircuit, GeneticCircuit> swapped_circuits(c_1, c_2);

  // Generate random index to split at
  std::uniform_int_distribution<> dist{
      input_no, (std::min(c_1.getGateCount(), c_2.getGateCount())) - 1};
  int split_index = dist(rand_engine);
  std::cout << "Past Here 2" << std::endl;

  std::pair<GeneticCircuit, GeneticCircuit> c_1_halves =
      split(c_1, split_index);
  std::cout << "Past Here 3" << std::endl;
  std::pair<GeneticCircuit, GeneticCircuit> c_2_halves =
      split(c_2, split_index);
  std::cout << "Past Here 4" << std::endl;

  swapped_circuits.first = splice(c_1_halves.first, c_2_halves.second);
  std::cout << "Past Here 5" << std::endl;
  swapped_circuits.second = splice(c_2_halves.first, c_1_halves.second);

  return swapped_circuits;
}

std::map<int, GeneticCircuit> Genetic::spawnPopulation(int populationSize) {
  std::map<int, GeneticCircuit> spawned_pop;
  while (spawned_pop.size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    int circuit_fitness = c.generateFitness();

    if (SHOW_POPULATION_LOG) {
      std::string errmsg =
          "Genetic::spawnPopulation inserting Circuit "
          "fitness: " +
          std::to_string(circuit_fitness);
      errlog(errmsg);
    }

    std::pair<int, GeneticCircuit> zergling(c.hash_circ(), c);
    spawned_pop.insert(zergling);

    if (SHOW_POPULATION_LOG) {
      std::ostringstream errstream;
      errstream << "Genetic::spawnPopulation --  " << spawned_pop.size();
      errlog(errstream.str(), SHOW_POPULATION_LOG);
    }
  }
  return spawned_pop;
}
