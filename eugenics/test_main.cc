#include "../../include/gtest/gtest.h"
#include "binary_gate.h"
#include "unary_gate.h"

TEST(AND, And) {
  EXPECT_EQ(0, And(0, 0).evaluate());
  EXPECT_EQ(0, And(0, 1).evaluate());
  EXPECT_EQ(1, And(1, 1).evaluate());
  EXPECT_EQ(0, And(1, 0).evaluate());
}

TEST(OR, Or) {
  EXPECT_EQ(0, Or(0, 0).evaluate());
  EXPECT_EQ(1, Or(0, 1).evaluate());
  EXPECT_EQ(1, Or(1, 1).evaluate());
  EXPECT_EQ(1, Or(1, 0).evaluate());
}

TEST(NOT, Not) {
  EXPECT_EQ(1, Not(0).evaluate());
  EXPECT_EQ(0, Not(1).evaluate());
}
