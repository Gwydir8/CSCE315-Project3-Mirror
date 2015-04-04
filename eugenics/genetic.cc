#include "genetic.h"

#include <string>
#include <iostream>
#include <functional>
#include <utility>    // std::map
#include <algorithm>  // std::max
#include <random>     // std::mt19937

#include <cstdio>
#include <cstdlib>
#include <ctime>  // std::time

#include "utility.h"

using std::string;
using std::vector;
using std::srand;
using std::rand;
using std::time;

Genetic::Genetic(int n, BooleanTable outputs)
    : input_no(n),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()) {
  population = spawnPopulation(1000);
}

Genetic::Genetic(int n, BooleanTable outputs, std::map<int, Circuit> pop)
    : population(pop),
      input_no(n),
      expected_outputs(outputs),
      rand_engine(std::random_device{}()){};

Genetic::~Genetic() {}

int Genetic::fitness(GeneticCircuit c) {
  int score = 0;
  score += c.getNotCount() * 10000;
  score += c.getAndCount() * 10;
  score += c.getOrCount() * 1;
  return score;
}

void Genetic::split(Circuit c1, Circuit c2) {
  // random numbers should be in normal distribution
  std::uniform_int_distribution<> dist{input_no, (int)expected_outputs.front().size()};
  for (int i = 0; i < 50; ++i) {
    std::string errmsg =
        "Genetic::split: random number: " + std::to_string(dist(rand_engine));
    errlog(errmsg);
  }
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




std::map<int, Circuit> Genetic::spawnPopulation(int populationSize) {
  std::map<std::string, Circuit> fake_pop;
  std::map<int, Circuit> spawned_pop;
  while(spawned_pop.size() < 1000) {
    GeneticCircuit c =
      GeneticCircuit(input_no, expected_outputs.front().size(), &rand_engine);
    int circuit_fitness = fitness(c);
    c.setFitness(circuit_fitness);

    std::string errmsg =
      "Genetic::spawnPopulation inserting Circuit fitness: " +
      std::to_string(circuit_fitness);
    errlog(errmsg);

    std::pair<int, Circuit> zergling(hash_circ(c), c);
    spawned_pop.insert(zergling);
    std::cout << "Currently has found: " << fake_pop.size() << " --  "<< spawned_pop.size() << std::endl;
  }
  return spawned_pop;
}

size_t hash_circ(GeneticCircuit c) {
  std::string s = "";
  std::hash<std::string> hash_fn;
  BooleanTable outputs = c.evaluateAllInputs();
  for (std::vector<bool> row : outputs) {
    for (bool bit : row) {
      s += std::to_string((int)bit);
    }
  }

  /* std::cout << "Hashing..." << std::endl; */
  size_t hash = hash_fn(s);
  /* std::cout << "Done Hashing..: " << hash << std::endl; */
  std::cout << " NOT: " << c.getNotCount() << " AND: " << c.getAndCount()
    << " OR: " << c.getOrCount() << std::endl;
  return hash;
}

