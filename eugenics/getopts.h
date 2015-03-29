#ifndef GETOPTS_H
#define GETOPTS_H

#include <iostream>
#include <string>

#include <cstring>
#include <cstdlib>   //exit
#include <unistd.h>  // getopt

#include "utility.h"

enum Algol_t { GENETIC, TRADITIONAL };

struct EugenicsConfig {
  Algol_t algol = GENETIC;
  char * hostname = "localhost";
  int port = 20000;
};

// print usage information
void usage() {
  std::cerr << "Group 15: CSCE315-503 Project 3" << std::endl;
  std::cerr << "usage: eugenics [OPTIONS]" << std::endl;
  std::cerr << "-h [HOSTNAME]"
            << "\t"
            << "hostname (default: localhost)" << std::endl;
  std::cerr << "-p [PORT]"
            << "\t"
            << "port (default: 20000)" << std::endl;
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

EugenicsConfig getOpts(int argc, char* argv[]) {
  // create config
  EugenicsConfig config;

  bool gen_flag = false;   // Use genetic algorithm
  bool trad_flag = false;  // Use traditional algorithm

  char * host = "localhost";
  int port = 20000;

  int arg;  // argument given
  while ((arg = getopt(argc, argv, "h:p:gt")) != -1) {
    switch (arg) {
      case 'h':  // hostname
        host = optarg;
        break;
      case 'p':  // port number
        port = std::atoi(optarg);
        break;
      case 'g':  // genetic algorithm
        // errlog("got genetic");
        gen_flag = true;
        break;
      case 't':  // traditional algorithm
        // errlog("got traditional");
        trad_flag = true;
        break;
      case '?':
      default:
        usage();
        std::exit(EXIT_FAILURE);
    }
  }

  if (trad_flag && !gen_flag) {
    // if trad_flag is true and the only flag set, algol is traditional
    config.algol = TRADITIONAL;
  } else {
    // all other combinations, algol is genetic
    config.algol = GENETIC;
  }

  config.hostname = host;
  config.port = port;


  return config;
}

#endif /* GETOPTS_H */
