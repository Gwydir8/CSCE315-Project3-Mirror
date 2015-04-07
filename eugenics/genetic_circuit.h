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
  virtual ~GeneticCircuit() {
  }

  void setFitness(int f) { fitness = f; }
  int getFitness() { return fitness; }
  // returns the smallest cut you can make without disturbing mappings..
  //
  void setMapping(std::vector<int> new_mapping){ mapped_outputs = new_mapping;}
  std::vector<int> getMapping(){ return mapped_outputs;}
  int getSmallestSafeCut();
  void mapOutputToOutput(int to_map, int index_to_be_mapped);
  std::size_t hash_circ();

 private:
  std::uniform_int_distribution<> gate_dist{0, 2};
  std::uniform_int_distribution<> number_dist{10, 36};
  std::mt19937* rand_engine_ptr;
  int fitness;
  /* BooleanTable memoized_output;//assuming that gates won't be added after
   * evaluation */
  /* bool has_memo; //flag to determine if output has been already calculated */
};

#endif
