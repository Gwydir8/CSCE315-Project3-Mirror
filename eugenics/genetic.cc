#include "genetic.h"

#include <string>
#include <iostream>
#include <utility>    //std::map
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

// don't we want this in genetic.h (outside class)? if it's here it's global
Circuit randomCircuit(int input_num, int output_num) {
  std::string errmsg = "randomCircuit " + std::to_string(input_num) +
                       " inputs; " + std::to_string(output_num) + " outputs";
  errlog(errmsg);

  if (input_num < 2) {
    std::string errmsg = "randomCircuit Need more than 2 inputs to create gate";
    errlog(errmsg);
    exit(-1);
  }
  Circuit c = Circuit(input_num, output_num);
  vector<GateType> gate = {NOT, OR, AND};
  int num_of_gates = 2;  // arbitrary...
  srand(time(NULL));
  for (int i = 0; i < num_of_gates; ++i) {
    num_of_gates = 0 + rand() % 30;  // random number between 1 and 30
    // random number between 0 and 2
    GateType rand_gate = gate[rand() % 2];

    if (rand_gate == NOT) {
      c.addGate(rand_gate, c.getGateCount());
    } else if (rand_gate == OR || rand_gate == AND) {
      c.addGate(rand_gate, c.getGateCount() - 2, c.getGateCount() - 1);
    }
  }
  return c;
}

Genetic::~Genetic() {}

int Genetic::fitness(Circuit c) {
  int score = 0;
  score += c.getNotCount() * 10000;
  score += c.getAndCount() * 10;
  score += c.getOrCount() * 1;
  return score;
}

void Genetic::split(Circuit c1, Circuit c2) {
  // create mersenne_twister_engine(mt19937)
  std::mt19937 rand_engine{std::random_device{}()};

  int num_inputs = std::max(c1.getInputCount(), c2.getInputCount());

  int max_split_index = (std::max(c1.getGateCount(), c2.getGateCount()) - 1);

  // random numbers should be in normal distribution
  std::uniform_int_distribution<> dist{num_inputs, max_split_index};

  for (int i = 0; i < 50; ++i) {
    std::cout << dist(rand_engine) << '\n';

    std::string errmsg =
        "Genetic::split: random number: " + std::to_string(dist(rand_engine));
    errlog(errmsg);
  }
}

void Genetic::splice() {}

void Genetic::splitAndSplice() {}

void Genetic::spawnPopulation(int populationSize) {
  for (int i = 0; i < populationSize; ++i) {
    int circuit_fitness = 0;
    Circuit c = randomCircuit(expected_inputs.size(), expected_outputs.size());
    circuit_fitness = fitness(c);
    std::string errmsg =
        "Genetic::spawnPopulation inserting Circuit fitness: " +
        std::to_string(circuit_fitness);
    errlog(errmsg);
    std::pair<int, Circuit> zergling(circuit_fitness, c);
    population.insert(zergling);
  }
}
