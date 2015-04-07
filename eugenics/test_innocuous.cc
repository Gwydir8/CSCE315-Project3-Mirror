#include "../../local/include/gtest/gtest.h"

#include <vector>

#include "genetic.h"
#include "genetic_circuit.h"
#include "circuit.h"
#include "utility.h"

// #define VERBOSE_TEST

TEST(InnocuousAttempt, XOR) {
  BooleanTable expected_o = {{false}, {true}, {true}, {false}};

  std::minstd_rand rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(2, 1, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;

  while ((answer != expected_o)) {
    ++i;
    delete c;
    c = new GeneticCircuit(2, 1, &rand);
    answer = c->evaluateAllInputs();
#ifdef VERBOSE_TEST
    if (i % 100000 == 0) {
      std::cerr << "Iteration: " + std::to_string(i) << std::endl;
      std::cerr << *c << std::endl;
    }
#endif
  }
  std::cerr << "Iteration: " + std::to_string(i) << std::endl;
  std::cerr << *c << std::endl;
  c->writeCircuitToFile();
  EXPECT_EQ(expected_o, answer);
}

TEST(InnocuousAttempt, FullAdder) {
  BooleanTable expected_o = {{false, false},
                             {false, true},
                             {false, true},
                             {true, false},
                             {false, true},
                             {true, false},
                             {true, false},
                             {true, true}};
  BooleanTable expected_o_bar = {{false, false},
                                 {true, false},
                                 {true, false},
                                 {false, true},
                                 {true, false},
                                 {false, true},
                                 {false, true},
                                 {true, true}};
  std::minstd_rand rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(3, 2, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;

  while ((answer != expected_o) || (answer != expected_o_bar)) {
    ++i;
    delete c;
    c = new GeneticCircuit(2, 2, &rand);
    answer = c->evaluateAllInputs();
#ifdef VERBOSE_TEST
    if (i % 10000 == 0) {
      std::cerr << "Iteration: " + std::to_string(i) << std::endl;
      std::cerr << *c << std::endl;
    }
#endif
  }
  std::cerr << "Iteration: " + std::to_string(i) << std::endl;
  std::cerr << *c << std::endl;
  c->writeCircuitToFile();
  EXPECT_EQ(expected_o, answer);
}

TEST(InnocuousAttempt, InvertInputs) {
  BooleanTable expected_o = {{true, true, true},
                             {true, true, false},
                             {true, false, true},
                             {true, false, false},
                             {false, true, true},
                             {false, true, false},
                             {false, false, true},
                             {false, false, false}};
  std::minstd_rand rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(3, 3, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;
  while ((answer != expected_o)) {
    ++i;
    delete c;
    c = new GeneticCircuit(3, 3, &rand);
    answer = c->evaluateAllInputs();
#ifdef VERBOSE_TEST
    if (i % 10000 == 0) {
      std::cerr << "Iteration: " + std::to_string(i) << std::endl;
      std::cerr << *c << std::endl;
    }
#endif
  }
  std::cerr << "Iteration: " + std::to_string(i) << std::endl;
  std::cerr << *c << std::endl;
  c->writeCircuitToFile();
  EXPECT_EQ(expected_o, answer);
}
