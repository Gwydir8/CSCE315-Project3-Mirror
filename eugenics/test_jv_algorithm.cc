#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include "gate.h"
#include "jvalgorithm.h"
#include <vector>
using namespace std;

TEST(JVAlgorithmTest, EmptyTest) {
  vector<vector<bool>> expected_output = {{false}, {true}};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(1, 1)).search(expected_output));
}


/*TEST(JVAlgorithmTest, ANDMatch)  {
  bool expected_output = true;
  Circuit c(2, 1);
  c.addGate(AND, 0, 1);
  vector<vector<bool>> desired_output = {{false}, {false}, {false}, {true}};
  Ckt_Algo check(c);

  EXPECT_EQ(expected_output, check.circuit_matches_desired(c, desired_output));
}*/

/*TEST(JVAlgorithmTest, DifferentWireMatch)  {
  bool expected_output = true;
  Circuit c (2,1);
  c.addGate(AND, 0,1);
  vector<vector<bool>> desired_output = {{false}, {false}, {true}, {true}};
  Ckt_Algo check (c);

  EXPECT_EQ(expected_output, check.circuit_matches_desired(c, desired_output));
}*/

/*TEST(JVAlgorithmTest, ANDTest) {
  vector<vector<bool>> expected_output = {{false}, {false}, {false}, {true}};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(2, 1)).search(expected_output));
}*/

/*TEST(JVAlgorithmTest, XORTest) {
  vector<vector<bool>> expected_output = {{false}, {true}, {true}, {false}};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(2, 1)).search(expected_output));
}*/

TEST(JVAlgorithmTest, FullAdderTest){
        vector<vector<bool>> expected_output = {{false, false},
                                           {false, true},
                                           {false, true},
                                           {true, false},
                                           {false, true},
                                           {true, false},
                                           {true, false},
                                           {true, true}};
    EXPECT_EQ(expected_output, Ckt_Algo(Circuit(3,2)).search(expected_output));
}

/*TEST(JVAlgorithmTest, Inverter1){
  vector<vector<bool>> expected_output = {{true}, {true}, {true};
  vector<bool> inputs = {false, false, false};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}


TEST(JVAlgorithmTest, Inverter2){
  vector<vector<bool>> expected_output = {{true}, {true}, {false};
  vector<bool> inputs = {false, false, true};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}

TEST(JVAlgorithmTest, Inverter3){
  vector<vector<bool>> expected_output = {{true}, {false}, {true};
  vector<bool> inputs = {false, true, false};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}

TEST(JVAlgorithmTest, Inverter4){
  vector<vector<bool>> expected_output = {{true}, {false}, {false};
  vector<bool> inputs = {false, true, true};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}

TEST(JVAlgorithmTest, Inverter5){
  vector<vector<bool>> expected_output = {{true}, {true}, {true};
  vector<bool> inputs = {true, false, false};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}

TEST(JVAlgorithmTest, Inverter6){
  vector<vector<bool>> expected_output = {{true}, {true}, {false};
  vector<bool> inputs = {true, false, true};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}

TEST(JVAlgorithmTest, Inverter7){
  vector<vector<bool>> expected_output = {{true}, {false}, {true};
  vector<bool> inputs = {true, true, false};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}

TEST(JVAlgorithmTest, Inverter8){
  vector<vector<bool>> expected_output = {{false}, {false}, {false};
  vector<bool> inputs = {true, true, true};
  EXPECT_EQ(expected_output, Ckt_Algo(Circuit(inputs, 3)).search(expected_output));
}*/






///./build/eugenics/test-jv_algorithm
///./debug/eugenics/test-jv_algorithm