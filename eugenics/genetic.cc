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

Genetic::Genetic(int n, BooleanTable outputs, int population_size)
    : input_no(n),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()) {
  population = spawnPopulation(population_size);
}

Genetic::Genetic(int n, BooleanTable outputs,
                 std::map<std::size_t, GeneticCircuit> pop)
    : population(pop),
      input_no(n),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()) {}

std::pair<std::vector<Gate *>, std::vector<Gate *>> Genetic::split(
    GeneticCircuit circuit, int split_index) {
  // split gates

  std::vector<Gate *> a = circuit.getGates();
  std::vector<Gate *> lhs_gates(a.begin(), a.begin() + split_index);
  std::vector<Gate *> rhs_gates(a.begin() + split_index, a.end());

  // split circuit and c2 into a and b at dist(rand_engine)
  return std::pair<std::vector<Gate *>, std::vector<Gate *>>(lhs_gates,
                                                             rhs_gates);
}

GeneticCircuit Genetic::splice(std::vector<Gate *> base_part,
                               std::vector<Gate *> appended_part) {
  std::vector<Gate *> combined_gates = base_part;
  std::vector<Gate *> a = appended_part;

  combined_gates.insert(std::end(combined_gates), std::begin(a), std::end(a));

  GeneticCircuit new_circuit(input_no, expected_outputs.front().size(),
                             &rand_engine, combined_gates);
  return new_circuit;
}

std::pair<GeneticCircuit, GeneticCircuit> Genetic::splitAndSplice(
    GeneticCircuit c_1, GeneticCircuit c_2) {
  std::pair<GeneticCircuit, GeneticCircuit> swapped_circuits(c_1, c_2);

  // Generate random index to split at
  std::uniform_int_distribution<> dist{
      input_no, (std::min(c_1.getGateCount(), c_2.getGateCount())) - 1};
  int split_index = dist(rand_engine);

  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_1_halves =
      split(c_1, split_index);
  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_2_halves =
      split(c_2, split_index);

  swapped_circuits.first = splice(c_1_halves.first, c_2_halves.second);
  swapped_circuits.second = splice(c_2_halves.first, c_1_halves.second);

  return swapped_circuits;
}

std::map<std::size_t, GeneticCircuit> Genetic::spawnPopulation(
    std::size_t populationSize) {

  std::map<std::size_t, GeneticCircuit> spawned_pop;
  while (spawned_pop.size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    int circuit_fitness = generateFitness(c);
    c.setFitness(circuit_fitness);

    if (SHOW_POPULATION_LOG) {
      std::string errmsg =
          "Genetic::spawnPopulation inserting Circuit "
          "fitness: " +
          std::to_string(c.getFitness());
      errlog(errmsg);
    }

    std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c);
    spawned_pop.insert(zergling);

    if (SHOW_POPULATION_LOG) {
      std::ostringstream errstream;
      errstream << "Genetic::spawnPopulation --  " << spawned_pop.size();
      errlog(errstream.str(), SHOW_POPULATION_LOG);
    }
  }
  return spawned_pop;
}


int Genetic::generateFitness(GeneticCircuit c) {
  int score = 0;
  BooleanTable actual_output = c.evaluateWithCache();
  for (int i = 0; i < actual_output.size(); ++i) {
      if(actual_output[i] != expected_outputs[i]){
        score += 100000;
      }
  }
  score += c.getNotCount() * 10000;
  score += (c.getOrCount() + c.getAndCount()) * 10;
  return score;
}

