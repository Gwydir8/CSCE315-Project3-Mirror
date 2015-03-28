#include "../../local/include/gtest/gtest.h"
// #include "circuit.h"
// #include "gate.h"
// #include <vector>
#include "getopts.h"

// TEST(TEST_GROUP_NAME, TEST_NAME) {
//
// }

TEST(GetOpts, default) {
  char bin[] = "eugenics";
  char* args[] = { bin };
  EXPECT_EQ(Algol_t(GENETIC), getOpts(1,args));
}

TEST(GetOpts, traditional) {
  char bin[] = "eugenics";
  char arg1[] = "-t";
  char* args[] = { bin, arg1 };
  EXPECT_EQ(Algol_t(TRADITIONAL), getOpts(2,args));
}

TEST(GetOpts, genetic) {
  char bin[] = "eugenics";
  char arg1[] = "-g";
  char* args[] = { bin, arg1 };
  EXPECT_EQ(Algol_t(GENETIC), getOpts(2,args));
}

TEST(GetOpts, both) {
  char bin[] = "eugenics";
  char arg1[] = "-g";
  char* args[] = { bin, arg1 };
  EXPECT_EQ(Algol_t(GENETIC), getOpts(2,args));
}

