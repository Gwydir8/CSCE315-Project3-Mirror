// Group 15: CSCE315-503 Project 3
// Eugenics
// main.cc

#include <iostream>
#include <string>

#include <cstdlib>  //exit

#include "getopts.h"
#include "genetic.h"
#include "genetic_circuit.h"
#include "circuit.h"
#include "utility.h"

int main(int argc, char* argv[]) {
  // get algorithm from CLI
  Algol_t algol = getOpts(argc, argv);

  if (algol == GENETIC) {
    errlog("Running Genetic Algorithm");

    // full adder
    BooleanTable expected_outputs = {{false, false},
                                     {false, true},
                                     {false, true},
                                     {true, false},
                                     {false, true},
                                     {true, false},
                                     {true, false},
                                     {true, true}};
    Genetic fulladder = Genetic(3, expected_outputs, 1000);

    std::cout << fulladder.evolve() << std::endl;

    // inverted outputs
    BooleanTable expected_outputs = {{true, true, true},
                                     {true, true, false},
                                     {true, false, true},
                                     {true, false, false},
                                     {false, true, true},
                                     {false, true, false},
                                     {false, false, true},
                                     {false, false, false}};
    Genetic inverted = Genetic(3, expected_outputs, 1000);

    std::cout << inverted.evolve() << std::endl;

  } else if (algol == TRADITIONAL) {
    errlog("Running Traditional Algorithm");
  }

  std::exit(EXIT_SUCCESS);
}
