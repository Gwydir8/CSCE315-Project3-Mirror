# Set Project_Name and Language
project(gauss CXX)

# version 3.0.0-rc5 is on compute.cse.tamu.edu
cmake_minimum_required(VERSION 3.0.0)

# set some compiler flags
# note DEBUG is set for debug build
# and NDEBUG is set for release build
if(${CMAKE_COMPILER_IS_GNUCXX})
  # gcc/g++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # clang flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")
endif()

# set project locations
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
# if we need to build documentation. useful for man pages
set(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}share")

# set cmake modules location
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/share/cmake)

# set library locations
if(APPLE)
  # if run on OS X
  # probably don't need to set these
elseif(UNIX)
  # if run on linux/unix

  # directory boost is installed to (--prefix)
  #set(BOOST_ROOT ~/usr/)
  # directory readline is installed to (--prefix)
  #set(Readline_ROOT_DIR ~/usr/)
endif()

# if we use gtest
# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
# option(test "Build ${PROJECT_NAME}'s tests" OFF)

# subdirectories to build.
# First variable is location of files, second is where binary will be put
add_subdirectory(${SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/bin)
# may need to build our libraries
#add_subdirectory(${LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/lib)