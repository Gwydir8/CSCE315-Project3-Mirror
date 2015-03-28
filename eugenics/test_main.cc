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

class CircuitTest : public testing::Test {
 protected:
  Circuit c = Circuit(2, 2);
};

// TEST(CircuitTest, ReturnAddGate) {
// }

TEST_F(CircuitTest, Simple) {
  // Circuit c(2, 2);
  std::vector<bool> expected_output{true, false};
  EXPECT_EQ(expected_output, c.evaluateInputSet({true, false}));
}

TEST_F(CircuitTest, LessSimple) {
  // Circuit c(2, 2);
  EXPECT_EQ(3, c.addGate(AND, 1, 1));
  EXPECT_EQ(4, c.addGate(WIRE, 0));
  std::vector<bool> expected_output{false, true};
  EXPECT_EQ(expected_output, c.evaluateInputSet({true, false}));
}

class XORTest : public testing::Test {
 protected:
  virtual void SetUp() {
    c = new Circuit(2, 1);
    // EXPECT_EQ(3, c->addGate(WIRE, 0));
    // EXPECT_EQ(4, c->addGate(WIRE, 1));
    // EXPECT_EQ(5, c->addGate(NOT, 0));
    // EXPECT_EQ(6, c->addGate(NOT, 1));
    // EXPECT_EQ(7, c->addGate(AND, 0, 3));
    // EXPECT_EQ(8, c->addGate(AND, 1, 2));
    // EXPECT_EQ(9, c->addGate(OR, 4, 5));
    // c->addGate(WIRE, 0);
    // c->addGate(WIRE, 1);
    c->addGate(NOT, 0);
    c->addGate(NOT, 1);
    c->addGate(AND, 0, 3);
    c->addGate(AND, 1, 2);
    c->addGate(OR, 4, 5);
  }
  virtual void TearDown() { delete c; }
  Circuit* c;
  Circuit cempty = Circuit(2, 1);
  std::vector<bool> expected_output0{false};
  std::vector<bool> expected_output1{true};
};

TEST_F(XORTest, XOR_wiretest) { EXPECT_EQ(2, cempty.numGates()); }

TEST_F(XORTest, XOR0) {
  // Circuit c(2, 1);
  /* EXPECT_EQ( ,  c.evaluateAllInputs()); */
  EXPECT_EQ(expected_output0, c->evaluateInputSet({false, false}));
}
TEST_F(XORTest, XOR1) {
  EXPECT_EQ(expected_output0, c->evaluateInputSet({true, true}));
}
TEST_F(XORTest, XOR2) {
  EXPECT_EQ(expected_output1, c->evaluateInputSet({false, true}));
}
TEST_F(XORTest, XOR3) {
  EXPECT_EQ(expected_output1, c->evaluateInputSet({true, false}));
}

// TEST_F(XORTest, XOR) {
//   // Circuit c(2, 1);
//   EXPECT_EQ(3, c.addGate(WIRE, 0));
//   EXPECT_EQ(4, c.addGate(WIRE, 1));
//   EXPECT_EQ(5, c.addGate(NOT, 0));
//   EXPECT_EQ(6, c.addGate(NOT, 1));
//   EXPECT_EQ(7, c.addGate(AND, 0, 3));
//   EXPECT_EQ(8, c.addGate(AND, 1, 2));
//   EXPECT_EQ(9, c.addGate(OR, 4, 5));
//   std::vector<bool> expected_output{false};
//   /* EXPECT_EQ( ,  c.evaluateAllInputs()); */
//   EXPECT_EQ(expected_output, c.evaluateInputSet({false, false}));
//   std::vector<bool> expected_output2{true};
//   EXPECT_EQ(expected_output, c.evaluateInputSet({true, true}));
//   EXPECT_EQ(expected_output2, c.evaluateInputSet({false, true}));
//   EXPECT_EQ(expected_output2, c.evaluateInputSet({true, false}));
// }

/* class CircuitSetup : public testing::Test { */
/*     Circuit c({true, false}); */
/* }; */

// TEST(SubCircuitTest, NOR) {
//   std::vector<Gate*> gates;
//   gates.push_back(new Not(0));
//   gates.push_back(new Or(0,1));
//   SubCircuit subcircuit(gates);
//   EXPECT_EQ(0, subcircuit.evaluate());
// }

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
