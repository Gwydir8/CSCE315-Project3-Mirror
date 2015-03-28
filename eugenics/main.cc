// Group 15: CSCE315-503 Project 3
// Eugenics
// main.cc

#include <iostream>
#include <string>

#include <cstdlib>   //exit
#include <unistd.h>  // getopt

#include "utility.h"

#include "getopts.h"

int main(int argc, char* argv[]) {
  // get algorithm from CLI
  Algol_t algol = getOpts(argc, argv);
  if (algol == GENETIC) {
    std::cout << "Running Genetic Algorithm" << std::endl;
  } else if (algol == TRADITIONAL) {
    std::cout << "Running Traditional Algorithm" << std::endl;
  }

  std::exit(EXIT_SUCCESS);
}
