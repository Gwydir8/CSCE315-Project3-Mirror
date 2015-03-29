#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include "circuit.h"

class Algo {
  private:
    std::queue<Circuit> ex_list;
	std::vector<std::vector<bool>> circ_output;
    int level = 1;
    int not_counter = 0;
    
  public:
    Algo();

    int check_output(Circuit x, std::vector<std::vector<bool>> desired);
    void add_not(int counter);
    void add_and(int counter);
    void add_or(int counter);
    std::vector<std::vector<bool>> search(std::vector<std::vector<bool>> desired);

};



#endif
