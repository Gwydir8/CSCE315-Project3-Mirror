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

int Genetic::fitness(GeneticCircuit c) {
  int score = 0;
  score += c.getNotCount() * 10000;
  score += c.getAndCount() * 10;
  score += c.getOrCount() * 1;
  return score;
}

void Genetic::split(GeneticCircuit c1, GeneticCircuit c2) {
  // random numbers should be in normal distribution
  std::uniform_int_distribution<> dist{input_no,
                                       (int)expected_outputs.front().size()};

  // first half size
  int split_num = dist(rand_engine);

  // split c1 and c2 into a and b at dist(rand_engine)
  GeneticCircuit c1a(c1);
  GeneticCircuit c1b(c1);
  std::vector<Gate *> c1agates(std::begin(c1.getGates()),
                               std::begin(c1.getGates()) + split_num);
  std::vector<Gate *> c1bgates(std::begin(c1.getGates()) + split_num,
                               std::end(c1.getGates()) + split_num);
  GeneticCircuit c2a(c2);
  GeneticCircuit c2b(c2);
  std::vector<Gate *> c2agates(std::begin(c2.getGates()),
                               std::begin(c2.getGates()) + split_num);
  std::vector<Gate *> c2bgates(std::begin(c2.getGates()) + split_num,
                               std::end(c2.getGates()) + split_num);
}

void Genetic::splice() {}

void Genetic::splitAndSplice() {}

std::map<int, GeneticCircuit> Genetic::spawnPopulation(int populationSize) {
  std::map<int, GeneticCircuit> spawned_pop;
  while (spawned_pop.size() < populationSize) {
    GeneticCircuit c(input_no, expected_outputs.front().size(), &rand_engine);
    int circuit_fitness = fitness(c);
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
