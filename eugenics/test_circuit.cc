#include "../../local/include/gtest/gtest.h"
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
  Circuit cempty = Circuit(2, 1);
  std::vector<bool> expected_output0{false};
  std::vector<bool> expected_output1{true};
};

TEST_F(XORTest, XOR_wiretest) { EXPECT_EQ(2, cempty.getGateCount()); }

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

    c->addGate(22, WIRE, 16);

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

TEST_F(FullAdderTest, FAMatrixSize) {
  EXPECT_EQ(matrix.size(), c->evaluateAllInputs().size());
}
TEST_F(FullAdderTest, FAEvalTotal) {
  EXPECT_EQ(matrix, c->evaluateAllInputs());
}

class CircuitTest : public testing::Test {
 protected:
  Circuit c = Circuit(2, 2);
};

TEST_F(CircuitTest, MappingOutput) {
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
  std::vector<bool> expected_output{false, true};
  EXPECT_EQ(expected_output, c.evaluateInputSet({true, false}));
}
