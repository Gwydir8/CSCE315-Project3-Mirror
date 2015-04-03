#include "../../local/include/gtest/gtest.h"
#include "genetic.h"
#include <vector>
using namespace std;
class GeneticSetup : public testing::Test {
 protected:
  virtual void SetUp() {
    // FUN FACT: dolly was the first cloned sheep! In honor of her...we send our
    // test genetic class into space with her title
    expected_inputs = {
        {false, false}, {false, true}, {true, false}, {true, true}};
    expected_outputs = {
        {false, false}, {false, true}, {true, false}, {true, true}};
    dolly = Genetic(expected_inputs, expected_outputs);
  }
  BooleanTable expected_inputs;
  BooleanTable expected_outputs;
  Genetic dolly;
};

TEST_F(GeneticSetup, Fitness) {
  Circuit c = Circuit(2,2);
  EXPECT_GT(0, dolly.fitness(c)); }
TEST_F(GeneticSetup, ConstructorTest) {
  int expected_population_size = 1000;  // This may change
  EXPECT_EQ(expected_inputs, dolly.getExpectedInputs());
  EXPECT_EQ(expected_outputs, dolly.getExpectedOutputs());
  EXPECT_EQ(expected_population_size, dolly.getPopulation().size());
}
/* TEST_F(GeneticSetup, Splice) { */

/* } */

/* TEST_F(GeneticSetup, Split) { */

/* } */
