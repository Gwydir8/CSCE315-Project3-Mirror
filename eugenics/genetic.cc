#include "genetic.h"

Circuit randomCircuit(int input_num, int output_num) {
  

}

Genetic::Genetic() {}

Genetic::~Genetic() {}

void Genetic::fitness() {}

void Genetic::spliceCircuit() {}

void Genetic::splitCircuit() {}

void Genetic::splitAndSplice() {}

void Genetic::spawnPopulation(int populationSize) {
  for (int i = 0; i < populationSize; ++i) {
    int initial_fitness = 0;
    std::pair<int, Circuit> zergling(
        initial_fitness,
        randomCircuit(expected_inputs.size(), expected_outputs.size()));
  }
}
