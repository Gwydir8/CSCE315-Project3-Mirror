#include "../../local/include/gtest/gtest.h"

#include "getopts.h"

// TEST(TEST_GROUP_NAME, TEST_NAME) {
//
// }

TEST(GetOpts, default) {
  // create config
  EugenicsConfig config;
  // defaults
  config.algol = GENETIC;
  config.hostname = "localhost";
  config.port = 20000;

  char bin[] = "eugenics";
  char* args[] = {bin};
  EugenicsConfig outputconf = getOpts(1, args);

  EXPECT_EQ(config.algol, outputconf.algol);
  EXPECT_EQ(config.hostname, outputconf.hostname);
  EXPECT_EQ(config.port, outputconf.port);
}

TEST(GetOpts, traditional) {
  // create config
  EugenicsConfig config;
  config.algol = TRADITIONAL;
  config.hostname = "localhost";
  config.port = 20000;

  char bin[] = "eugenics";
  char arg1[] = "-t";
  char* args[] = {bin, arg1};
  EugenicsConfig outputconf = getOpts(2, args);

  EXPECT_EQ(config.algol, outputconf.algol);
  EXPECT_EQ(config.hostname, outputconf.hostname);
  EXPECT_EQ(config.port, outputconf.port);
}

TEST(GetOpts, genetic) {
  // create config
  EugenicsConfig config;
  config.algol = GENETIC;
  config.hostname = "localhost";
  config.port = 20000;

  char bin[] = "eugenics";
  char arg1[] = "-g";
  char* args[] = {bin, arg1};
  EugenicsConfig outputconf = getOpts(2, args);

  EXPECT_EQ(config.algol, outputconf.algol);
  EXPECT_EQ(config.hostname, outputconf.hostname);
  EXPECT_EQ(config.port, outputconf.port);
}

TEST(GetOpts, both) {
  // create config
  EugenicsConfig config;
  config.algol = GENETIC;
  config.hostname = "localhost";
  config.port = 20000;

  char bin[] = "eugenics";
  char arg1[] = "-gt";
  char* args[] = {bin, arg1};
  EugenicsConfig outputconf = getOpts(2, args);

  EXPECT_EQ(config.algol, outputconf.algol);
  EXPECT_EQ(config.hostname, outputconf.hostname);
  EXPECT_EQ(config.port, outputconf.port);
}

TEST(GetOpts, hostname) {
  // create config
  EugenicsConfig config;
  config.algol = GENETIC;
  config.hostname = "Tron.local";
  config.port = 20000;

  char bin[] = "eugenics";
  char arg1[] = "-h";
  char arg2[] = "Tron.local";
  char* args[] = {bin, arg1, arg2};
  EugenicsConfig outputconf = getOpts(3, args);

  EXPECT_EQ(config.algol, outputconf.algol);
  EXPECT_EQ(config.hostname, outputconf.hostname);
  EXPECT_EQ(config.port, outputconf.port);
}

TEST(GetOpts, port) {
  // create config
  EugenicsConfig config;
  config.algol = GENETIC;
  config.hostname = "localhost";
  config.port = 10000;

  char bin[] = "eugenics";
  char arg1[] = "-p";
  char arg2[] = "10000";
  char* args[] = {bin, arg1, arg2};
  EugenicsConfig outputconf = getOpts(3, args);

  EXPECT_EQ(config.algol, outputconf.algol);
  EXPECT_EQ(config.hostname, outputconf.hostname);
  EXPECT_EQ(config.port, outputconf.port);
}
