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

  errlog("Started s&s", true);
  // Generate random index to split at
  std::uniform_int_distribution<> dist{
      input_no, (std::min(c_1.getGateCount(), c_2.getGateCount())) - 1};

  int split_index = dist(rand_engine);

  if (c_1.getGateCount() <= input_no || c_2.getGateCount() <= input_no) {
    split_index = input_no;
  }

  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_1_halves =
      split(c_1, split_index);
  std::pair<std::vector<Gate *>, std::vector<Gate *>> c_2_halves =
      split(c_2, split_index);

  swapped_circuits.first = splice(c_1_halves.first, c_2_halves.second);
  swapped_circuits.second = splice(c_2_halves.first, c_1_halves.second);

  return swapped_circuits;
}

/* void GeneticCircuit::insertIntoPopulation(GeneticCircuit c){ */
/*   c.setFitness(generateFitness(c)); */
/*   std::pair<std::size_t, GeneticCircuit> zergling(c.hash_circ(), c); */
/*   population.insert(zergling); */
/* } */

std::map<std::size_t, GeneticCircuit> Genetic::spawnPopulation(
    std::size_t populationSize) {
  std::map<std::size_t, GeneticCircuit> spawned_pop;
  while (spawned_pop.size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    c.setFitness(generateFitness(c));

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

void Genetic::cullHerd() {
  int avg = 0;
  double total = 0.0;
  std::map<std::size_t, GeneticCircuit>::iterator it;
  for (it = population.begin(); it != population.end(); ++it) {
    int fit = generateFitness((*it).second);
    total += fit;
    avg = total / population.size();
  }
  it = population.begin();
  while (it != population.end()) {
    if (generateFitness((*it).second) > avg) {
      population.erase(it++);
    } else {
      ++it;
    }
  }

  errlog("I should be done", true);
  std::string errmsg =
      "Deleted stuff. Population is now: " + std::to_string(population.size());
  errlog(errmsg, true);
  errlog("I should be done", true);
}

GeneticCircuit Genetic::evolve(){
  while(!correct_found){
    cullHerd();
    std::vector<GeneticCircuit *> breedable;
    std::map<std::size_t, GeneticCircuit>::iterator it;
    for (it = population.begin(); it != population.end(); ++it) {
      breedable.push_back(&(it->second));
    }
    errlog("not yet", true);

    for (std::size_t i = 0; i < breedable.size() - 2; i += 2) {
      errlog("Ran..", true);
      std::pair<GeneticCircuit, GeneticCircuit> twins =
          splitAndSplice(*breedable[i], *breedable[i + 1]);
      twins.first.setFitness(generateFitness(twins.first));
      population.insert(std::pair<std::size_t, GeneticCircuit>(
          twins.first.hash_circ(), twins.first));
      twins.second.setFitness(generateFitness(twins.second));
      population.insert(std::pair<std::size_t, GeneticCircuit>(
          twins.second.hash_circ(), twins.second));
    }
    errlog("Done", true);
  }

  return population.at(hashExpectedOutput());
}

int Genetic::generateFitness(GeneticCircuit c) {
  int score = 0;
  BooleanTable actual_output = c.evaluateAllInputs();
  for (std::size_t i = 0; i < actual_output.size(); ++i) {
    if (actual_output[i] != expected_outputs[i]) {
      score += 10000;
    }
  }
  score += c.getNotCount() * 1000;
  score += (c.getOrCount() + c.getAndCount()) * 10;
  if (score < 10000) {
    correct_found = true;
  }
  return score;
}

size_t Genetic::hashExpectedOutput(){
  std::string s = "";
  std::hash<std::string> hash_fn;
  for (std::vector<bool> row : expected_outputs) {
    for (bool bit : row) {
      s += std::to_string((int)bit);
    }
  }
  std::size_t hash = hash_fn(s);
  return hash;
}

