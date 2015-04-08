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

    std::size_t initial_population_size = 1000;
    int inputs = 3;
    BooleanTable expected_outputs = {{false, false},
                                     {false, true},
                                     {false, true},
                                     {true, false},
                                     {false, true},
                                     {true, false},
                                     {true, false},
                                     {true, true}};
    Genetic dolly = Genetic(inputs, expected_outputs, initial_population_size);

    std::cout << dolly.evolve() << std::endl;

  } else if (algol == TRADITIONAL) {
    errlog("Running Traditional Algorithm");
  }

  std::exit(EXIT_SUCCESS);
}
