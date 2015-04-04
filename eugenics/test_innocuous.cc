#include "../../local/include/gtest/gtest.h"

#include <vector>

#include "genetic.h"
#include "genetic_circuit.h"
#include "circuit.h"
#include "utility.h"

TEST(InnocuousAttempt, NumberTwo) {
  BooleanTable expected_o = {{true, true, true},
                             {true, true, false},
                             {true, false, true},
                             {true, false, false},
                             {false, true, true},
                             {false, true, false},
                             {false, false, true},
                             {false, false, false}};
  std::mt19937 rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(3, 3, &rand);
  while (c->evaluateAllInputs() != expected_o) {
    delete c;
    c = new GeneticCircuit(3, 3, &rand);
  }
}
