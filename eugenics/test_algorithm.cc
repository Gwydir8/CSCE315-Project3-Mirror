#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include "gate.h"
#include "traditional_algorithm.h"
#include <vector>
using namespace std;
TEST(TraditionalAlgorithmTest, ConstructorTest) {
  vector<vector<bool>> expected_output = {{true, false}, {true, false}};
  Circuit basic = Circuit(3, 2);
  TraditionalAlgorithm alg = TraditionalAlgorithm(basic, expected_output);
  EXPECT_EQ(expected_output, alg.getOuputSet());
  EXPECT_EQ(basic.evaluateAllInputs(),
            alg.getRootCircuit().evaluateAllInputs());
}
TEST(AlgorithmTest, SimpleSearchTest) {
  vector<vector<bool>> expected_output = {
      {true, false}, {true, true}, {false, false}, {false, true}};
  Circuit basic = Circuit(2, 2);
  TraditionalAlgorithm alg = TraditionalAlgorithm(basic, expected_output);
  Circuit result = alg.findMatchingCircuit();
  EXPECT_EQ(expected_output, result.evaluateAllInputs());
}
