#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include "gate.h"
#include "jvalgorithm.h"
#include <vector>
using namespace std;

TEST(JVAlgorithmTest, EmptyTest){
	vector<vector<bool>> expected_output = { {false}, {true}};
	EXPECT_EQ(expected_output, Ckt_Algo(Circuit(1,1)).search(expected_output));
}

TEST(JVAlgorithmTest, ANDTest){
	vector<vector<bool>> expected_output = {{false}, {false}, {false}, {true}};
	EXPECT_EQ(expected_output, Ckt_Algo(Circuit(2,1)).search(expected_output));
}

/*TEST(JVAlgorithmTest, XORTest){
	vector<vector<bool>> expected_output = {{false}, {true}, {true}, {false}};
	EXPECT_EQ(expected_output, Ckt_Algo(Circuit(2,1)).search(expected_output));
}*/

/*TEST(JVAlgorithmTest, FullAdderTest){
	vector<vector<bool>> expected_output = {{false, false},
                                           {false, true},
                                           {false, true},
                                           {true, false},
                                           {false, true},
                                           {true, false},
                                           {true, false},
                                           {true, true}};
    EXPECT_EQ(expected_output, Ckt_Algo(Circuit(3,2)).search(expected_output));
}*/

///./build/eugenics/test-jv_algorithm
///./debug/eugenics/test-jv_algorithm