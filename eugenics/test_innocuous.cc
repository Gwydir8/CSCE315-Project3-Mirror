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
  BooleanTable expected_o = {{false},
                             {true}
                             {false},
                             {true}};
  BooleanTable expected_o = {{false},
                             {true}
                             {true},
                             {false}};

  std::mt19937 rand(std::random_device{}());
  // std::minstd_rand0 rand(std::random_device{}());
  GeneticCircuit* c = new GeneticCircuit(2, 1, &rand);
  BooleanTable answer = c->evaluateAllInputs();
  int i = 0;

  // #ifdef THREADED
  // std::vector<std::future<BooleanTable>> boolean_table_futures;
  // #endif THREADED

  while ((answer != expected_o) || (answer != expected_o_bar)) {
    // #ifdef THREADED
    // for (int i = 0; i < (NUM_CORES - 1); ++i) {
    //   boolean_table_futures.push_back(
    //       std::async(std::launch::async, , points));
    // }
    // #endif THREADED

    // std::vector<Path> paths;  // vector of possible paths
    // // Calculate a path on main thread while waiting for other threads
    // // If we're doing more than 1 set, do NUM_SETS random path calculations
    // on
    // // main thread
    // for (int i = 0; i < NUM_SETS; i++) {
    //   paths.push_back(FindRandomPath(points));
    // }

    // // Get Paths from threads
    // for (auto& pathfuture : pathfutures) {
    //   paths.push_back(pathfuture.get());
    // }

    delete c;
    c = new GeneticCircuit(2, 1, &rand);
    std::cerr << "Iteration: " + std::to_string(++i) << std::endl;
    // std::cerr << *c << std::endl;
    answer = c->evaluateAllInputs();
  }
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

  // #ifdef THREADED
  // std::vector<std::future<BooleanTable>> boolean_table_futures;
  // #endif THREADED

  while ((answer != expected_o) || (answer != expected_o_bar)) {
    // #ifdef THREADED
    // for (int i = 0; i < (NUM_CORES - 1); ++i) {
    //   boolean_table_futures.push_back(
    //       std::async(std::launch::async, , points));
    // }
    // #endif THREADED

    // std::vector<Path> paths;  // vector of possible paths
    // // Calculate a path on main thread while waiting for other threads
    // // If we're doing more than 1 set, do NUM_SETS random path calculations
    // on
    // // main thread
    // for (int i = 0; i < NUM_SETS; i++) {
    //   paths.push_back(FindRandomPath(points));
    // }

    // // Get Paths from threads
    // for (auto& pathfuture : pathfutures) {
    //   paths.push_back(pathfuture.get());
    // }

    delete c;
    c = new GeneticCircuit(3, 2, &rand);
    std::cerr << "Iteration: " + std::to_string(++i) << std::endl;
    // std::cerr << *c << std::endl;
    answer = c->evaluateAllInputs();
  }
}

// TEST(InnocuousAttempt, InvertInputs) {
//   BooleanTable expected_o = {{true, true, true},
//                              {true, true, false},
//                              {true, false, true},
//                              {true, false, false},
//                              {false, true, true},
//                              {false, true, false},
//                              {false, false, true},
//                              {false, false, false}};
//   std::mt19937 rand(std::random_device{}());
//   // std::minstd_rand0 rand(std::random_device{}());
//   GeneticCircuit* c = new GeneticCircuit(3, 3, &rand);
//   while (c->evaluateAllInputs() != expected_o) {
//     delete c;
//     c = new GeneticCircuit(3, 3, &rand);
//     std::cerr << *c << std::endl;
//   }
// }
