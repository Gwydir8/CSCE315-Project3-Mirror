// Group 15: CSCE315-503 Project 3
// Eugenics
// main.cc

#include <iostream>
#include <string>

#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>   //exit

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "getopts.h"
#include "utility.h"

int main(int argc, char* argv[]) {
  // get algorithm from CLI
  Algol_t algol = getOpts(argc, argv);
  if (algol == GENETIC) {
    errlog("Running Genetic Algorithm");
  } else if (algol == TRADITIONAL) {
    errlog("Running Traditional Algorithm");
  }

  std::exit(EXIT_SUCCESS);
}
