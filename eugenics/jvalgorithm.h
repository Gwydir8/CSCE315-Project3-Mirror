#ifndef JVALGORITHM_H
#define JVALGORITHM_H

#include <vector>
#include <queue>
#include "circuit.h"

class Ckt_Algo {
 public:
  // Circuit Constructor
  Ckt_Algo(Circuit circuit);
  // ex_list.front()'s output
  std::vector<std::vector<bool>> circ_output;
  // returns true if circuit.evaluateAllInputs() matches desired
  // it also uses output_set to store all the unique outputs and
  // compares them to ex_list.front() 
  bool circuitMatchesDesired(std::vector<std::vector<bool>> desired);
  // searches for circuit that matches desired output
  // if found, search is complete
  std::vector<std::vector<bool>> search(std::vector<std::vector<bool>> desired);

 private:
  // exhaustive list, a queue of search-generated circuits
  std::queue<Circuit> ex_list;
  // helper functions to creating the population
  void addNot(int counter);
  void addAnd(int counter);
  void addOr(int counter);
  // instantiate vector on heap
  std::vector<std::vector<std::vector<bool>>>* output_set;
};

#endif