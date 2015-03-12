#!/bin/bash
# build project3. should be run in root of project.
# USAGE: cd $PROJECT_ROOT; ./share/build.sh

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
if [ "$HOSTNAME" = "sun2.cs.tamu.edu" ]; then
    CORES=8
elif [ "$HOSTNAME" = "compute-linux1" ]; then
    # hell yeah
    CORES=32
else
    CORES=4
fi

echo "Starting Release Build..."

# create and switch to build dir
mkdir build;
cd build;
# generate release build make files
cmake -DCMAKE_BUILD_TYPE=Release ..
# make on all cores
make -j"$CORES"
echo "Release Build Done!"

echo "Starting Debug Build..."

# cd back to project root
cd ..
# create and switch to build dir
mkdir debug;
cd debug;
# generate debug build make files
cmake -DCMAKE_BUILD_TYPE=Debug ..
# make on all cores
make -j"$CORES"
echo "Debug Build Done!"

# cd back to project root
cd ..

echo "Release Build PROJECT_ROOT/build/"
echo "Debug Build PROJECT_ROOT/debug/"
