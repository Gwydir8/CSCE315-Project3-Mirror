// Group 15: CSCE315-503 Project 3
// Eugenics
// main.cc

#include <iostream>
#include <string>

/* // gflags */
/* // strip help from binary */
/* //#define STRIP_FLAG_HELP 1 */
/* #include <gflags/gflags.h> */

/* // define cli arguments */
/* DEFINE_string(algorithm, "genetic", "Choice of algorithm"); */
/* DEFINE_bool(verbose, false, "Print verbose messages"); */

/* // validates algorithm flags */
/* static bool validate_algorithm(const char* flag_name, const std::string& algo) { */
/*   if ((algo == "genetic") || (algo == "traditional")) { */
/*     return true; */
/*   } else { */
/*     std::cerr << "Invalid value for --" << std::string(flag_name) << ": " */
/*               << algo << std::endl; */
/*     return false; */
/*   } */
/* } */

/* // register validator */
/* static const bool algo_validated = */
/*     gflags::RegisterFlagValidator(&FLAGS_algorithm, &validate_algorithm); */

int main(int argc, char* argv[]) {
  // set version
  /* gflags::SetVersionString("0.0.1"); */
  /* // help string */
  /* std::string usagemsg = */
  /*   std::string( "Usage:\n" ) + std::string(argv[0]) + " [OPTIONS] filename"; */
  /* gflags::SetUsageMessage(usagemsg); */
  /* // parse and validate flags */
  /* gflags::ParseCommandLineFlags(&argc, &argv, true); */

  std::cout << "Group 15: CSCE315-503 Project 3" << std::endl;

  return 0;
}
