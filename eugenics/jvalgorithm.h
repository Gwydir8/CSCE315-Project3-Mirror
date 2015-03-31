#ifndef JVALGORITHM_H
#define JVALGORITHM_H

#include <vector>
#include "circuit.h"

class Ckt_Algo {
 private:
  // exhaustive list, a vector of search-generated circuits
  std::vector<Circuit> ex_list;

  // ex_list.front()'s output
  std::vector<std::vector<bool>> circ_output;

  void add_not(int counter);
  void add_and(int counter);
  void add_or(int counter);

 public:
  // Circuit Constructor
  Ckt_Algo(Circuit circuit);

  // returns true if circuit.evaluateAllInputs() matches desired
  bool circuit_matches_desired(Circuit circuit,
                               std::vector<std::vector<bool>> desired);
  // searches for circuit that matches desired output
  // if found, search is complete
  std::vector<std::vector<bool>> search(std::vector<std::vector<bool>> desired);
};

#endif