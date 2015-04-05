#ifndef GENETIC_CIRCUIT_H
#define GENETIC_CIRCUIT_H

#include <vector>
#include <random>

#include <utility>
#include <random>     // std::minstd_rand
#include <algorithm>  // std::max
#include <cstddef>    //std::size_t

#include "circuit.h"

// show debug logging for spawnPopulation
const bool SHOW_POPULATION_LOG = false;

class GeneticCircuit : public Circuit {
 public:
  GeneticCircuit(int input_num, int output_num, std::minstd_rand* rand_eng_ptr);
  GeneticCircuit(int input_num, int output_num, std::minstd_rand* rand_eng_ptr,
                 std::vector<Gate*> gates);
  // virtual ~GeneticCircuit() {
  //   std::cerr << __FUNCTION__ << std::endl;  // << *this << std::endl;
  // }

  void setFitness(int f) { fitness = f; }
  BooleanTable evaluateWithCache();
  int getFitness() { return fitness; }

  std::size_t hash_circ();

 private:
  std::uniform_int_distribution<> gate_dist{0, 2};
  std::uniform_int_distribution<> number_dist{0, 28};
  std::minstd_rand* rand_engine_ptr;
  int fitness;
  BooleanTable memoized_output;//assuming that gates won't be added after evaluation
  bool has_memo; //flag to determine if output has been already calculated
};

#endif
