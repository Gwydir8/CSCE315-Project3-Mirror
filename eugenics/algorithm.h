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

  int check_output(Circuit x, std::vector<std::vector<bool>> desired);
  void add_not(int counter);
  void add_and(int counter);
  void add_or(int counter);
  std::vector<std::vector<bool>> search(std::vector<std::vector<bool>> desired);

 private:
  std::queue<Circuit> ex_list;
  std::vector<std::vector<bool>> circ_output;
};

#endif
