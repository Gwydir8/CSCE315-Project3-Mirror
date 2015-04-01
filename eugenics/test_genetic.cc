#include "../../local/include/gtest/gtest.h"
#include "genetic.h"
#include <vector>
using namespace std;
class GeneticSetup : public testing::Test {
 protected:
  virtual void SetUp() {
    //FUN FACT: dolly was the first cloned sheep! In honor of her...we send our
    //test genetic class into space with her title
    dolly = Genetic(expected_inputs, expected_outputs);
    expected_inputs = {{false, false}, {false, true}, {true, false}, {true, true}};
    expected_outputs = {{false, false}, {false, true}, {true, false}, {true, true}};
  }
  BooleanTable expected_inputs;
  BooleanTable expected_outputs;
  Genetic dolly;
};

TEST_F(GeneticSetup, ConstructorTest) {
  int expected_population_size = 1000; //This may change
  EXPECT_EQ(expected_inputs, dolly.getExpectedInputs());
  EXPECT_EQ(expected_outputs, dolly.getExpectedOutputs());
  EXPECT_EQ(expected_population_size, dolly.getPopulation().size());
}
TEST_F(GeneticSetup, Fitness) {
  EXPECT_GT(0, dolly.fitness());
}
/* TEST_F(GeneticSetup, Splice) { */

/* } */

/* TEST_F(GeneticSetup, Split) { */

/* } */