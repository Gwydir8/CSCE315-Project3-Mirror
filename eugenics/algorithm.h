#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include "circuit.h"

class Algo {
 public:
  // default constructor
  Algo();

  // circuit constructor
  Algo(Circuit circuit);

  // searches for circuit that matches desired output
  // if found, search is complete
  std::vector<std::vector<bool>> search(std::vector<std::vector<bool>> desired);

 private:
  // exhaustive list, a queue of search-generated circuits
  std::queue<Circuit> ex_list;

  // ex_list.front()'s output
  std::vector<std::vector<bool>> circ_output;

  // returns true if circuit.evaluateAllInputs() matches desired
  bool circuit_matches_desired(Circuit circuit,
                               std::vector<std::vector<bool>> desired);

  // generates different circuits based on the different
  // combinations of gates to wires, then pushes to queue
  void add_not(int counter);
  void add_and(int counter);
  void add_or(int counter);
};

#endif
