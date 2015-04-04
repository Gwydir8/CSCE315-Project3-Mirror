#ifndef GENETIC_CIRCUIT_H
#define GENETIC_CIRCUIT_H

#include <vector>
#include <random>

#include <utility>
#include <random>     // std::mt19937
#include <algorithm>  // std::max
#include <cstddef>    //std::size_t

#include "circuit.h"

// show debug logging for spawnPopulation
const bool SHOW_POPULATION_LOG = false;

class GeneticCircuit : public Circuit {
 public:
  GeneticCircuit(int input_num, int output_num, std::mt19937* rand_eng_ptr);
  GeneticCircuit(int input_num, int output_num, std::mt19937* rand_eng_ptr,
                 std::vector<Gate*> gates);

  void setFitness(int f);

  std::size_t hash_circ();

 private:
  std::uniform_int_distribution<> gate_dist{0, 2};
  std::uniform_int_distribution<> number_dist{0, 40};
  std::mt19937* rand_engine_ptr;
  int fitness;
};

#endif
