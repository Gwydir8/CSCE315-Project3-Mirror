#include <iostream>
#include <string>

// gflags
#define STRIP_FLAG_HELP 1
#include <gflags/gflags.h>

// validates algolrithm flags
static bool validate_algorithm(const char* flag_name,
                               const std::string& algol) {
  // need to change search to whatever our other choice is
  if ((algol == "genetic") || (algol == "search")) {
    return true;
  } else {
    // printf("Invalid value for --%s: %d\n", flagname, (int)value);
    return false;
  }
}

DEFINE_string(algorithm, "genetic", "Choice of algorithm");

static const bool algol_validated =
    gflags::RegisterFlagValidator(&FLAGS_algorithm, &validate_algorithm);

int main(int argc, char* argv[]) {
  // parse and validate flags
  gflags::SetUsageMessage(
      "Group 15: CSCE315-503 Project 3's Circuit Generator.\n"
      "Usage:\n"
      "\t--algorithm\tSet the type of algorithm to use (Default: genetic, "
      "options: genetic, search)\n"
      "\n"
      "Example:\n"
      "\tgauss --algorithm=genetic truth_table.txt\n");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::cout << "Group 15: CSCE315-503 Project 3" << std::endl;

  return 0;
}
