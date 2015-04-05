#include "../../local/include/gtest/gtest.h"

#include <vector>

#include "genetic.h"
#include "genetic_circuit.h"
#include "circuit.h"
#include "utility.h"

namespace {

class GeneticSetup : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // FUN FACT: dolly was the first cloned sheep! In honor of her...we send our
    // test genetic class into space with her title
    expected_population_size = 1000;
    expected_i = 3;
    expected_o = {{true, true, true},
                  {true, true, false},
                  {true, false, true},
                  {true, false, false},
                  {false, true, true},
                  {false, true, false},
                  {false, false, true},
                  {false, false, false}};
    dolly = Genetic(expected_i, expected_o);
  }

  Genetic dolly;
  std::size_t expected_population_size;
  int expected_i;
  BooleanTable expected_o;
};

TEST(GeneticCircuitFitnessTest, Fitness) {
  std::minstd_rand rand(std::random_device{}());
  GeneticCircuit c(3, 3, &rand);
  // It's expect EXPECTED is less than ACTUAL
  /* EXPECT_LT(0, c.generateFitness()); */
}

TEST_F(GeneticSetup, ConstructorTest) {
  // try having genetic only instantiate Circuit *s that are new GeneticCircuits
  // std::size_t expected_population_size = 1000;
  // int expected_i = 3;
  // BooleanTable expected_o = {{true, true, true},
  //                            {true, true, false},
  //                            {true, false, true},
  //                            {true, false, false},
  //                            {false, true, true},
  //                            {false, true, false},
  //                            {false, false, true},
  //                            {false, false, false}};
  // Genetic dolly(expected_i, expected_o);
  int actual_i = dolly.getExpectedInputs();
  EXPECT_EQ(expected_i, actual_i);
  BooleanTable actual_o = dolly.getExpectedOutputs();
  EXPECT_EQ(expected_o, actual_o);
  std::size_t actual_pop_size = dolly.getPopulation().size();
  EXPECT_EQ(expected_population_size, actual_pop_size);
}

TEST_F(GeneticSetup, Splice) {
  EXPECT_EQ(expected_population_size, dolly.getPopulation().size());
  // dolly.split(dolly.getPopulation()[3], dolly.getPopulation()[900]);
}

TEST_F(GeneticSetup, SplitAndSplice) {
  std::minstd_rand rand1(std::random_device{}());
  GeneticCircuit gc_1(3, 3, &rand1);
  GeneticCircuit gc_2(3, 3, &rand1);
  std::pair<GeneticCircuit, GeneticCircuit> gc_pair =
      dolly.splitAndSplice(gc_1, gc_2);

  int total_and_gates = gc_1.getAndCount() + gc_2.getAndCount();
  int total_or_gates = gc_1.getOrCount() + gc_2.getOrCount();
  int total_not_gates = gc_1.getNotCount() + gc_2.getNotCount();

  GeneticCircuit spliced_gc_1 = gc_pair.first;
  GeneticCircuit spliced_gc_2 = gc_pair.second;

  int spliced_total_and_gates =
      spliced_gc_1.getAndCount() + spliced_gc_2.getAndCount();
  int spliced_total_or_gates =
      spliced_gc_1.getOrCount() + spliced_gc_2.getOrCount();
  int spliced_total_not_gates =
      spliced_gc_1.getNotCount() + spliced_gc_2.getNotCount();

  EXPECT_EQ(total_and_gates, spliced_total_and_gates);
  EXPECT_EQ(total_or_gates, spliced_total_or_gates);
  EXPECT_EQ(total_not_gates, spliced_total_not_gates);
  // dolly.split(dolly.getPopulation()[3], dolly.getPopulation()[900]);
}

}  // end of namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
