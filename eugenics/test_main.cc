#include "../../include/gtest/gtest.h"
#include "circuit.h"
#include <vector>
#include "gate.h"

// TEST(TEST_GROUP_NAME, TEST_NAME) {
//
// }
TEST(WireTest, Wire) {
    Wire wire_1 = Wire(true);
    EXPECT_EQ(1, wire_1.evaluate());
}
class WireSetup : public testing::Test {
    protected:
        virtual void SetUp() {
            wire_1 = new Wire(true);
            wire_0 = new Wire(false);
        }
        Wire* wire_1;
        Wire* wire_0;
};

TEST_F(WireSetup, And) {
  EXPECT_EQ(0, And(wire_0, wire_0).evaluate());
  EXPECT_EQ(0, And(wire_0, wire_1).evaluate());
  EXPECT_EQ(1, And(wire_1, wire_1).evaluate());
  EXPECT_EQ(0, And(wire_1, wire_0).evaluate());
}

TEST_F(WireSetup, Or) {
  EXPECT_EQ(0, Or(wire_0, wire_0).evaluate());
  EXPECT_EQ(1, Or(wire_0, wire_1).evaluate());
  EXPECT_EQ(1, Or(wire_1, wire_1).evaluate());
  EXPECT_EQ(1, Or(wire_1, wire_0).evaluate());
}

TEST_F(WireSetup, Not) {
  EXPECT_EQ(1, Not(wire_0).evaluate());
  EXPECT_EQ(0, Not(wire_1).evaluate());
}

TEST_F(WireSetup, NAND) {
  EXPECT_EQ(1, Not(new And(wire_0, wire_0)).evaluate());
  EXPECT_EQ(1, Not(new And(wire_0, wire_1)).evaluate());
  EXPECT_EQ(0, Not(new And(wire_1, wire_1)).evaluate());
  EXPECT_EQ(1, Not(new And(wire_1, wire_0)).evaluate());
}

TEST_F(WireSetup, NOR) {
  EXPECT_EQ(1, Not(new Or(wire_0, wire_0)).evaluate());
  EXPECT_EQ(0, Not(new Or(wire_0, wire_1)).evaluate());
  EXPECT_EQ(0, Not(new Or(wire_1, wire_1)).evaluate());
  EXPECT_EQ(0, Not(new Or(wire_1, wire_0)).evaluate());
}

TEST(Circuit, Simple) {
    Circuit c({true, false});
    std::vector<bool> expected_output{true, false};
    EXPECT_EQ(expected_output, c.evaluate());
}

TEST(Circuit, LessSimple) {
    Circuit c({true, false});
    c.addGate(AND, 1, 1);
    c.addGate(WIRE, 0);
    std::vector<bool> expected_output{true, true};
    EXPECT_EQ(expected_output, c.evaluate());
}

// TEST(SubCircuitTest, NOR) {
//   std::vector<Gate*> gates;
//   gates.push_back(new Not(0));
//   gates.push_back(new Or(0,1));
//   SubCircuit subcircuit(gates);
//   EXPECT_EQ(0, subcircuit.evaluate());
// }

