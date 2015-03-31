#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include "gate.h"
#include "algorithm.h"
#include <vector>

using namespace std;

TEST(JVAlgorithmTest, EmptyTest) {
  vector<vector<bool>> expected_output = {{false}, {true}};
  EXPECT_EQ(expected_output, Algo(Circuit(1,1)).search(expected_output));
}

// TEST(JVAlgorithmTest, SimpleSearchTest) {
//   vector<vector<bool>> expected_output = {{false, false},
//                                           {false, true},
//                                           {false, true},
//                                           {true, false},
//                                           {false, true},
//                                           {true, false},
//                                           {true, false},
//                                           {true, true}};
//   Algo algorithm_test = Algo(Circuit(3,2));
//   vector<vector<bool>> result = algorithm_test.search(expected_output);
//   EXPECT_EQ(expected_output, result);
// }
