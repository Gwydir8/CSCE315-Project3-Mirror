#include "genetic.h"

Circuit randomCircuit(int input_num, int output_num) {}

Genetic::~Genetic() {}

int Genetic::fitness() { return 0; }

void Genetic::splice() {}

void Genetic::split() {}

void Genetic::splitAndSplice() {}

void Genetic::spawnPopulation(int populationSize) {
  for (int i = 0; i < populationSize; ++i) {
    int initial_fitness = 0;
    std::pair<int, Circuit> zergling(
        initial_fitness,
        randomCircuit(expected_inputs.size(), expected_outputs.size()));
  }
}
