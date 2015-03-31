#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include "gate.h"
#include "jvalgorithm.h"
#include <vector>
using namespace std;

TEST(JVAlgorithmTest, EmptyTest){
	vector<vector<bool>> expected_output = { {false}, {true}};
	EXPECT_EQ(expected_output, Algo(Circuit(1,1)).search(expected_output));
}






///./build/eugenics/test-jv_algorithm
///./debug/eugenics/test-jv_algorithm