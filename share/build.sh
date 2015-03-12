#!/bin/bash
# build project3. should be run in root of project.
# USAGE: cd $PROJECT_ROOT; ./share/build.sh

echo "Starting Release Build..."

# create and switch to build dir
mkdir build;
cd build;
# generate release build make files
cmake -DCMAKE_BUILD_TYPE=Release ..
# make on four cores
make -j4
echo "Release Build Done!"

echo "Starting Debug Build..."

# cd back to project root
cd ..
# create and switch to build dir
mkdir debug;
cd debug;
# generate debug build make files
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
# cd back to project root
cd ..
echo "Debug Build Done!"

echo "Release Build PROJECT_ROOT/build/"
echo "Debug Build PROJECT_ROOT/debug/"
