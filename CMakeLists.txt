# Set Project_Name and Language
project(eugenics CXX)

# version 3.0.0-rc5 is on compute.cse.tamu.edu
cmake_minimum_required(VERSION 3.0.0)

# set some compiler flags
# note DEBUG is set for debug build
# and NDEBUG is set for release build
if(${CMAKE_COMPILER_IS_GNUCXX})
  # gcc/g++ flags
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -Wall -Wextra -DDEBUG")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # OS X clang flags (use libc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -stdlib=libc++")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -Wall -Wextra -DDEBUG")
  else()
    # linux clang flags (use libstdc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libstdc++")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -Wall -Wextra -DDEBUG")
  endif()
endif()

# set project locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LOCAL_DIR "${CMAKE_SOURCE_DIR}/local")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
# if we need to build documentation. useful for man pages
set(SHARE_DIR "${CMAKE_SOURCE_DIR}/share")

# set cmake prefix
set(CMAKE_PREFIX_PATH
  ${CMAKE_PREFIX_PATH}
  ${LOCAL_DIR})
# set cmake modules location
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_LIST_DIR}/local/lib/cmake/gflags")
else()
  set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_LIST_DIR}/share/cmake"
    "${CMAKE_CURRENT_LIST_DIR}/local/lib/cmake/gflags")
endif()
# set cmake library path
set(CMAKE_LIBRARY_PATH
  ${CMAKE_LIBRARY_PATH}
  "${LOCAL_DIR}/lib")
# include local/include
include_directories("${LOCAL_DIR}/include")
include_directories("${LOCAL_DIR}/include/gflags")

# set library locations
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # if run on OS X
  # probably don't need to set these
else()
  # if run on linux/unix
  
  set(GFlags_ROOT_DIR include/gflags-2.1.1)
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
add_subdirectory(${SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/src/bin)
# may need to build our libraries
#add_subdirectory(${LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/lib)