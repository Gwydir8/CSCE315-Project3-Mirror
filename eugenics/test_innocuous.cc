#include "../../local/include/gtest/gtest.h"

#include <vector>

// uncomment to use threads
//#define THREADED

#ifdef THREADED

// Tron
//#define NUM_CORES 4
// Clue
#define NUM_CORES 12

#include <thread>
#include <future>

#endif  // THREADED

#include "genetic.h"
#include "genetic_circuit.h"
#include "circuit.h"
#include "utility.h"

TEST(InnocuousAttempt, XOR) {
  BooleanTable expected_o = {{false}, {true}, {false}, {true}};
  BooleanTable expected_o_bar = {{false}, {true}, {true}, {false}};

  std::mt19937 rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(2, 1, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;

  while ((answer != expected_o) || (answer != expected_o_bar)) {
    ++i;
    delete c;
    c = new GeneticCircuit(2, 1, &rand);
    if (i % 100000 == 0) {
      std::cerr << "Iteration: " + std::to_string(i) << std::endl;
      std::cerr << *c << std::endl;
    }
    answer = c->evaluateAllInputs();
  }
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
  std::mt19937 rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(3, 2, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;

  while ((answer != expected_o) || (answer != expected_o_bar)) {
    ++i;
    delete c;
    c = new GeneticCircuit(2, 2, &rand);
    if (i % 10000 == 0) {
      std::cerr << "Iteration: " + std::to_string(i) << std::endl;
      std::cerr << *c << std::endl;
    }
    answer = c->evaluateAllInputs();
  }
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
  std::mt19937 rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(3, 3, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;
  while ((answer != expected_o)) {
    ++i;
    delete c;
    c = new GeneticCircuit(3, 3, &rand);
    if (i % 10000 == 0) {
      std::cerr << "Iteration: " + std::to_string(i) << std::endl;
      std::cerr << *c << std::endl;
    }
    answer = c->evaluateAllInputs();
  }
}
