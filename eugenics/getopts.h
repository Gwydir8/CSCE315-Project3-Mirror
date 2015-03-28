#ifndef GETOPTS_H
#define GETOPTS_H

#include <iostream>
#include <string>

#include <cstring>
#include <cstdlib>   //exit
#include <unistd.h>  // getopt

#include "utility.h"

enum Algol_t { GENETIC, TRADITIONAL };

// print usage information
void usage() {
  std::cerr << "Group 15: CSCE315-503 Project 3" << std::endl;
  std::cerr << "usage: eugenics [OPTION]" << std::endl;
  std::cerr << "-g"
            << "\t"
            << "genetic algorithm (default)" << std::endl;
  std::cerr << "-t"
            << "\t"
            << "traditional algorithm" << std::endl;
  std::cerr << "  "
            << "\t"
            << "if both -g and -t are specified, -g is used." << std::endl;
}

Algol_t getOpts(int argc, char** argv) {
  bool gen_flag = false;   // Use genetic algorithm
  bool trad_flag = false;  // Use traditional algorithm

  int arg;  // argument given
  while ((arg = getopt(argc, argv, "gt")) != -1) {
    switch (arg) {
      case 'g':  // genetic algorithm
        gen_flag = true;
        break;
      case 't':  // traditional algorithm
        trad_flag = true;
        break;
      case 'h':  // -h is often help
      case '?':
      default:
        usage();
        std::exit(EXIT_FAILURE);
    }
  }

  if (trad_flag && !gen_flag) {
    // if trad_flag is true and the only flag set, return traditional
    return Algol_t(TRADITIONAL);
  } else {
    // all other combinations, return genetic
    return Algol_t(GENETIC);
  }
}


#endif /* GETOPTS_H */
