# Unit Tests
add_executable("test-getopts" src/test_getopts.cc ${SRCS})
add_executable("test-circuit" src/test_circuit.cc ${SRCS})
# add_executable("test-algorithm" src/test_algorithm.cc ${SRCS})
# add_executable("test-jv_algorithm" src/test_jv_algorithm.cc ${SRCS})
add_executable("test-visualize" src/test_visualize.cc ${SRCS})
add_executable("test-genetic" src/test_genetic.cc ${SRCS})
add_executable("test-innocuous" src/test_innocuous.cc ${SRCS})

# linking
target_link_libraries("test-getopts" gtest gtest_main)
target_link_libraries("test-circuit" gtest gtest_main)
# target_link_libraries("test-algorithm" gtest gtest_main)
# target_link_libraries("test-jv_algorithm" gtest gtest_main)
target_link_libraries("test-visualize" gtest gtest_main)
target_link_libraries("test-genetic" gtest gtest_main)
target_link_libraries("test-innocuous" gtest gtest_main)
