/* **********************Author Info************************** */
/* *@author    Christopher Findeisen                         * */
/* *@contact    <cfindeisen7@gmail.com>                      * */
/* *@date     Sat 28 Mar 14:44:55 2015                       * */
/* *********************************************************** */
//header
#ifndef TRADITIONAL_ALGORITHM_H
#define TRADITIONAL_ALGORITHM_H
#include <iostream>
#include "circuit.h"
#include <vector>
#include <queue>

class TraditionalAlgorithm {
  private:
    Circuit root;
    std::vector<std::vector<bool> > expected_output;
  public:
    /* TraditionalAlgorithm(){} */
    TraditionalAlgorithm(Circuit c, std::vector<std::vector<bool> > output_set): root(c), expected_output(output_set){};

    Circuit getRootCircuit() const{ return root; }
    std::vector<std::vector<bool> > getOuputSet() const {return expected_output;}
    //stubs for test function
    Circuit findMatchingCircuit() {return root;}
};

#endif
