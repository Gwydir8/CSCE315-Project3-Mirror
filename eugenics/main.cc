// Group 15: CSCE315-503 Project 3
// Eugenics
// main.cc

#include <iostream>
#include <string>

#include <cstdlib>  //exit

#include "getopts.h"
#include "jvalgorithm.h"
#include "genetic.h"
#include "genetic_circuit.h"
#include "circuit.h"
#include "utility.h"

int main(int argc, char* argv[]) {
  // get algorithm from CLI
  Algol_t algol = getOpts(argc, argv);

  BooleanTable fulladder_outputs = {{false, false},
                                    {false, true},
                                    {false, true},
                                    {true, false},
                                    {false, true},
                                    {true, false},
                                    {true, false},
                                    {true, true}};

  BooleanTable inverted_outputs = {{true, true, true},
                                   {true, true, false},
                                   {true, false, true},
                                   {true, false, false},
                                   {false, true, true},
                                   {false, true, false},
                                   {false, false, true},
                                   {false, false, false}};

  if (algol == GENETIC) {
    errlog("Running Genetic Algorithm");

    // full adder
    Genetic fulladder = Genetic(3, fulladder_outputs, 1000);
    std::cout << fulladder.evolve().writeCircuitToFile() << std::endl;

    // inverted outputs
    Genetic inverted = Genetic(3, inverted_outputs, 1000);
    std::cout << inverted.evolve().writeCircuitToFile() << std::endl;

  } else if (algol == TRADITIONAL) {
    errlog("Running Traditional Algorithm");

    // full adder
    Ckt_Algo fulladder_trad = Ckt_Algo(Circuit(3, 2));
    fulladder_trad.search(fulladder_outputs);
    std::cout << fulladder_trad.correct_circuit.writeCircuitToFile() << std::endl;

    // inverted outputs
    Ckt_Algo inverted_trad = Ckt_Algo(Circuit(3, 3));
    inverted_trad.search(inverted_outputs);
    std::cout << inverted_trad.correct_circuit.writeCircuitToFile() << std::endl;
  }

  std::exit(EXIT_SUCCESS);
}
