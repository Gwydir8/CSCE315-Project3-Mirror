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
  std::uniform_int_distribution<> dist{input_no,
                                       (int)expected_outputs.front().size()};
  for (int i = 0; i < 50; ++i) {
    std::string errmsg =
        "Genetic::split: random number: " + std::to_string(dist(rand_engine));
    errlog(errmsg);
  }
}

void Genetic::splice() {}

void Genetic::splitAndSplice() {}

std::map<int, Circuit> Genetic::spawnPopulation(int populationSize) {
  for (int i = 0; i < populationSize; ++i) {
    GeneticCircuit c =
        GeneticCircuit(input_no, expected_outputs.front().size());
    int circuit_fitness = fitness(c);
    c.setFitness(circuit_fitness);

    std::string errmsg =
        "Genetic::spawnPopulation inserting Circuit fitness: " +
        std::to_string(circuit_fitness);
    errlog(errmsg);

    std::pair<int, Circuit> zergling(hash_circ(c), c);
    population.insert(zergling);
  }
  return population;
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

  std::cout << "Hashing..." << std::endl;
  size_t hash = hash_fn(s);
  std::cout << "Done Hashing..: " << hash << std::endl;
  std::cout << " NOT: " << c.getNotCount() << " AND: " << c.getAndCount()
            << " OR: " << c.getOrCount();
  return hash;
}
