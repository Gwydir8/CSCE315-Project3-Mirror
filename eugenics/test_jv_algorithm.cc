#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include "gate.h"
#include "algorithm.h"
#include <vector>

using namespace std;

TEST(AlgorithmTest, SimpleSearchTest) {
  vector<vector<bool>> expected_output = {
      {false, false}};
  Circuit basic = Circuit(3, 2);
  Algo algorithm_test = Algo();
  // Circuit result = alg.findMatchingCircuit();
  vector<vector<bool>> result = algorithm_test.search(expected_output);
  EXPECT_EQ(expected_output, result);
}