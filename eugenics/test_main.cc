#include "../../include/gtest/gtest.h"

#include "subcircuit.h"
#include "unary_gate.h"
#include "binary_gate.h"

// TEST(TEST_GROUP_NAME, TEST_NAME)

TEST(LogicGateTest, And) {
  EXPECT_EQ(0, And(0, 0).evaluate());
  EXPECT_EQ(0, And(0, 1).evaluate());
  EXPECT_EQ(1, And(1, 1).evaluate());
  EXPECT_EQ(0, And(1, 0).evaluate());
}

TEST(LogicGateTest, Or) {
  EXPECT_EQ(0, Or(0, 0).evaluate());
  EXPECT_EQ(1, Or(0, 1).evaluate());
  EXPECT_EQ(1, Or(1, 1).evaluate());
  EXPECT_EQ(1, Or(1, 0).evaluate());
}

TEST(LogicGateTest, Not) {
  EXPECT_EQ(1, Not(0).evaluate());
  EXPECT_EQ(0, Not(1).evaluate());
}

TEST(ComboTests, NAND) {
  EXPECT_EQ(1, Not(And(0, 0).evaluate()).evaluate());
  EXPECT_EQ(1, Not(And(0, 1).evaluate()).evaluate());
  EXPECT_EQ(0, Not(And(1, 1).evaluate()).evaluate());
  EXPECT_EQ(1, Not(And(1, 0).evaluate()).evaluate());
}

TEST(ComboTests, NOR) {
  EXPECT_EQ(1, Not(Or(0, 0).evaluate()).evaluate());
  EXPECT_EQ(0, Not(Or(0, 1).evaluate()).evaluate());
  EXPECT_EQ(0, Not(Or(1, 1).evaluate()).evaluate());
  EXPECT_EQ(0, Not(Or(1, 0).evaluate()).evaluate());
}

TEST(SubCircuitTest, And) {
  SubCircuit subcircuit();
  subcircuit.insert_gate(And(0,1));
  EXPECT_EQ(0, subcircuit.evaluate());
}

TEST(SubCircuitTest, NOR) {
  SubCircuit subcircuit();
  subcircuit.insert_gate(Not(0,1));
  subcircuit.insert_gate(Or(0,1));
  EXPECT_EQ(0, subcircuit.evaluate());
}

// class SubCircuitTest : public testing::Test {
//  protected:
//   virtual void SetUp() {
//     subcircuit.insert_gate(And(0,1));
//     // subcircuit.insert_gate(Not(0));
//   }

//   SubCircuit subcircuit;
// };
