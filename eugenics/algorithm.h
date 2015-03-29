#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include "circuit.h"

class Algo {
  private:
    std::queue<Circuit> ex_list;
    int level = 1;
    int not_counter = 3;
    
  public:
    Algo();

    int check_output(Circuit x, std::vector<bool> sum, std::vector<bool> c_out);
    void add_not(int counter);
    void add_and(int counter);
    void add_or(int counter);
    Circuit search(std::vector<bool> sum, std::vector<bool> c_out);

}



#endif
