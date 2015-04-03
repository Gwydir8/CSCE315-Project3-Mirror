#include "../../local/include/gtest/gtest.h"
#include "genetic.h"
#include <vector>
using namespace std;
namespace {
int expected_i = 3;

BooleanTable expected_o = {{true, true, true},
                           {true, true, false},
                           {true, false, true},
                           {true, false, false},
                           {false, true, true},
                           {false, true, false},
                           {false, false, true},
                           {false, false, false}};
Genetic g = Genetic(expected_i, expected_o);
std::map<int, Circuit> pop = g.spawnPopulation(1000);
class GeneticSetup : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // FUN FACT: dolly was the first cloned sheep! In honor of her...we send our
    // test genetic class into space with her title
    dolly = Genetic(2, expected_o, pop);
  }
  GeneticSetup() {}
  Genetic dolly;
};

TEST_F(GeneticSetup, Fitness) {
  GeneticCircuit c = GeneticCircuit(2, 2);
  // It's expect EXPECTED is less than ACTUAL
  EXPECT_LT(0, dolly.fitness(c));
}
TEST_F(GeneticSetup, ConstructorTest) {
  unsigned long expected_population_size = 1000;  // This may change
  EXPECT_EQ(expected_i, dolly.getExpectedInputs());
  EXPECT_EQ(expected_o, dolly.getExpectedOutputs());
  EXPECT_EQ(expected_population_size, dolly.getPopulation().size());
}

TEST_F(GeneticSetup, Splice) {
  unsigned expected_population_size = 1000;  // This may change
  EXPECT_EQ(expected_population_size, dolly.getPopulation().size());
  // dolly.split(dolly.getPopulation()[3], dolly.getPopulation()[900]);
}

}  // end of namespace
/* TEST_F(GeneticSetup, Split) { */

/* } */
