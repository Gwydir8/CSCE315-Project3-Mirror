#include "../../local/include/gtest/gtest.h"
#include "circuit.h"
#include <vector>
#include "gate.h"

// TEST(TEST_GROUP_NAME, TEST_NAME) {
//
// }

TEST(WireTest, Wire) {
  Wire wire_1 = Wire(true, 0);
  EXPECT_EQ(1, wire_1.evaluate());
}
class WireSetup : public testing::Test {
 protected:
  virtual void SetUp() {
    wire_1 = new Wire(true, 0);
    wire_0 = new Wire(false, 1);

    and_00 = new And(wire_0, wire_0);
    and_01 = new And(wire_0, wire_1);
    and_10 = new And(wire_1, wire_0);
    and_11 = new And(wire_1, wire_1);

    or_00 = new Or(wire_0, wire_0);
    or_01 = new Or(wire_0, wire_1);
    or_10 = new Or(wire_1, wire_0);
    or_11 = new Or(wire_1, wire_1);
  }
  virtual void TearDown() {
    delete wire_1;
    delete wire_0;
    delete and_00;
    delete and_01;
    delete and_10;
    delete and_11;
    delete or_00;
    delete or_01;
    delete or_10;
    delete or_11;
  }
  Gate* wire_1;
  Gate* wire_0;
  Gate* and_00;
  Gate* and_01;
  Gate* and_10;
  Gate* and_11;
  Gate* or_00;
  Gate* or_01;
  Gate* or_10;
  Gate* or_11;
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
  EXPECT_EQ(1, Not(and_00).evaluate());
  EXPECT_EQ(1, Not(and_01).evaluate());
  EXPECT_EQ(0, Not(and_11).evaluate());
  EXPECT_EQ(1, Not(and_10).evaluate());
}

TEST_F(WireSetup, NOR) {
  EXPECT_EQ(1, Not(or_00).evaluate());
  EXPECT_EQ(0, Not(or_01).evaluate());
  EXPECT_EQ(0, Not(or_11).evaluate());
  EXPECT_EQ(0, Not(or_10).evaluate());
}

class XORTest : public testing::Test {
 protected:
  virtual void SetUp() {
    c = new Circuit(2, 1);
    c->addGate(NOT, 0);
    c->addGate(NOT, 1);
    c->addGate(AND, 0, 3);
    c->addGate(AND, 1, 2);
    c->addGate(OR, 4, 5);
  }
  virtual void TearDown() { delete c; }
  Circuit* c;
  std::vector<bool> expected_output0{false};
  std::vector<bool> expected_output1{true};
};

TEST(XORWIRETest, XOR_wiretest) {
  Circuit cempty = Circuit(2, 1);
  EXPECT_EQ(2, cempty.getGateCount());
}

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
  c->writeCircuitToFile();
  EXPECT_EQ(expected_output1, c->evaluateInputSet({true, false}));
}

/* TEST_F(FullAdderTest, FA_matrix_size) { EXPECT_EQ(matrix[0].size(),
 * c->evaluateAllInputs()[0].size()); } */

class FullAdderTest : public testing::Test {
 protected:
  virtual void SetUp() {
    c = new Circuit(3, 2);
    // this is mapped to this picture:
    // http://www.gamezero.com/team-0/articles/math_magic/micro/fulladder.gif
    // 3 NOTS in picture
    c->addGate(3, NOT, 0);  // first
    c->addGate(4, NOT, 1);  // second
    c->addGate(5, NOT, 2);  // third

    // first triple AND gate
    c->addGate(6, AND, 4, 2);
    c->addGate(7, AND, 6, 3);

    // second triple AND GATE
    c->addGate(8, AND, 0, 4);
    c->addGate(9, AND, 8, 5);

    // third triple AND GATE
    c->addGate(10, AND, 3, 1);
    c->addGate(11, AND, 10, 5);

    // fourth triple AND GATE
    c->addGate(12, AND, 0, 1);
    c->addGate(13, AND, 12, 2);

    // SuperOR AKA quadruple OR gate
    c->addGate(14, OR, 7, 9);
    c->addGate(15, OR, 11, 13);
    c->addGate(16, OR, 14, 15);

    // first double AND gate
    c->addGate(17, AND, 0, 2);
    // second double AND gate
    c->addGate(18, AND, 0, 1);
    // third double AND gate
    c->addGate(19, AND, 1, 2);
    // triple OR gate
    c->addGate(20, OR, 17, 18);
    c->addGate(21, OR, 20, 19);

    // c->addGate(22, WIRE, 16);
    c->mapGateToOutput((16), 1);  // maps input 1 to output 2
    c->mapGateToOutput((21), 0);  // maps input 1 to output 2

    matrix = {{false, false},
              {false, true},
              {false, true},
              {true, false},
              {false, true},
              {true, false},
              {true, false},
              {true, true}};
  }
  virtual void TearDown() { delete c; }
  Circuit* c;
  std::vector<std::vector<bool>> matrix;
};

TEST_F(FullAdderTest, FAEvalTotal) {
  c->writeCircuitToFile();
  EXPECT_EQ(matrix.size(), c->evaluateAllInputs().size());
  EXPECT_EQ(matrix, c->evaluateAllInputs());
}

class CircuitTest : public testing::Test {
 protected:
  Circuit c = Circuit(2, 2);
};

TEST_F(CircuitTest, MappingOutput) {
  c.writeCircuitToFile();
  c.mapGateToOutput(0, 1);  // maps input 1 to output 2
  std::vector<bool> expected_output{true, true};
  EXPECT_EQ(expected_output, c.evaluateInputSet({true, false}));
}

TEST_F(CircuitTest, Simple) {
  // Circuit c(2, 2);
  std::vector<bool> expected_output{true, false};
  EXPECT_EQ(expected_output, c.evaluateInputSet({true, false}));
}

TEST_F(CircuitTest, LessSimple) {
  // Circuit c(2, 2);
  EXPECT_EQ(2, c.addGate(2, AND, 1, 1));
  EXPECT_EQ(3, c.addGate(WIRE, 0));
  c.writeCircuitToFile();
  std::vector<bool> expected_output{false, true};
  EXPECT_EQ(expected_output, c.evaluateInputSet({true, false}));
}
