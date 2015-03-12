#!/bin/bash
# build project3. should be run in root of project.
# USAGE: cd $PROJECT_ROOT; ./build.sh

# get username
USER=`whoami`
# get os
UNAME=`uname`
# get hostname
if [ "$UNAME" = "Darwin" ]; then
    # if os x
    HOSTNAME=`hostname -s`
else
    # if not os x
    HOSTNAME=`hostname`
fi

# set number of cores for each server
# set compilers
if [ "$HOSTNAME" = "sun2.cs.tamu.edu" ]; then
    CORES=8
elif [ "$HOSTNAME" = "compute-linux1" ]; then
    # hell yeah
    CORES=32
    CC=/usr/bin/gcc-4.7
    CXX=/usr/bin/g++-4.7
else
    CORES=4
fi

RELEASE_BUILD_DIR="build"
DEBUG_BUILD_DIR="debug"

echo "Starting Release Build..."

# create and switch to build dir
if [ -d "$RELEASE_BUILD_DIR" ]; then
mkdir "$RELEASE_BUILD_DIR";
fi

cd "$RELEASE_BUILD_DIR";
# generate release build make files
cmake -DCMAKE_BUILD_TYPE=Release ..
# make on all cores
CC="$CC" CXX="$CXX" make -j"$CORES"
echo "Release Build Done!"

echo "Starting Debug Build..."

# cd back to project root
cd ..
# create and switch to build dir
if [ -d "$DEBUG_BUILD_DIR" ]; then
mkdir "$DEBUG_BUILD_DIR";
fi
cd "$DEBUG_BUILD_DIR";
# generate debug build make files
CC="$CC" CXX="$CXX" cmake -DCMAKE_BUILD_TYPE=Debug ..
# make on all cores
make -j"$CORES"
echo "Debug Build Done!"

# cd back to project root
cd ..

echo "Release Build PROJECT_ROOT/$RELEASE_BUILD_DIR/"
echo "Debug Build PROJECT_ROOT/$DEBUG_BUILD_DIR/"
