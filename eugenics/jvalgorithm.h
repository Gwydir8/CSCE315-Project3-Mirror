#ifndef JVALGORITHM_H
#define JVALGORITHM_H

#include <vector>
#include <queue>
#include "circuit.h"

class Ckt_Algo {
 private:
  // exhaustive list, a vector of search-generated circuits
  std::queue<Circuit> ex_list;

  void add_not(int counter);
  void add_and(int counter);
  void add_or(int counter);
  std::vector<std::vector<std::vector<bool>>>* output_set;

 public:
  // Circuit Constructor
  Ckt_Algo(Circuit circuit);
  // ex_list.front()'s output
  std::vector<std::vector<bool>> circ_output;
  // returns true if circuit.evaluateAllInputs() matches desired
  bool circuit_matches_desired(std::vector<std::vector<bool>> desired);
  // searches for circuit that matches desired output
  // if found, search is complete
  std::vector<std::vector<bool>> search(std::vector<std::vector<bool>> desired);
};

#endif