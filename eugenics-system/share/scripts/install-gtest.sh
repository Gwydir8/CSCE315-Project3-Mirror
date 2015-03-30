#!/bin/bash
# install gtest
# USAGE: cd $PROJECT_ROOT; ./install-gtest.sh

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

# set some directories and files
PROJECT_ROOT_DIR=`pwd`
PROJECT_SYSTEM_DIR=$PROJECT_ROOT_DIR

# DL_DIR="/tmp/TEAM15_DL"

# GTEST_URL="https://github.com/schuhschuh/gtest/archive/v2.1.1.tar.gz"
# if [ "$UNAME" = "Darwin" ]; then
#     GTEST_TAR_FILENAME="`basename $GTEST_URL`"
# else
#     GTEST_TAR_FILENAME="`basename $GTEST_URL .tar.gz`"
# fi
GTEST_INSTALL_DIR="$PROJECT_SYSTEM_DIR/eugenics-system/local/include/gtest"

echo "Checking if you have gtest..."
if [ -d "$GTEST_INSTALL_DIR" ]; then
    echo "You have gtest."
else
    # if you don't have gtest
    echo "You don't have gtest"

    # cd $PROJECT_ROOT_DIR
    # echo "Pulling Googletest 1.7.0"
    # git submodule update --init
    # cd $PROJECT_SYSTEM_DIR/eugenics-system
    # cd libraries
    # # build
    # echo "Building..."
    # if [ ! -d "gtest_build" ]; then
    #     mkdir gtest_build
    # fi
    # cd gtest_build
    # cmake ../googletest/.
    # make -j${CORES}

    # cd $PROJECT_SYSTEM_DIR/eugenics-system/local/lib
    # ln -s ../../libraries/eugenics-system/libraries/gtest_build/libgtest.a .
    # ln -s ../../libraries/eugenics-system/libraries/gtest_build/libgtest_main.a .

    # set up symlink
    # cd $PROJECT_SYSTEM_DIR/eugenics-system/local/include
    # ln -s ../../libraries/googletest/include/gtest .
    cd $PROJECT_SYSTEM_DIR/eugenics-system/local/include
    ln -s ../../libraries/googletest/include/gtest .

    echo "Done Installing googletest!"
fi

# echo "Checking if you have gtest..."
# if [ -d "$GTEST_INSTALL_DIR" ]; then
#     echo "You have gtest."
# else
#     # if you don't have gtest
#     echo "You don't have gtest"

#     # download if you don't have it
#     if [ ! -d "$DL_DIR" ]; then
#         # if dldir doesn't exist create it
#         mkdir -p "$DL_DIR"
#         # download gtest
#         echo "Downloading gtest"
#         wget --no-check-certificate -P "$DL_DIR" "$GTEST_URL" #>> "$LOGFILE" 2>&1
#     else
#         # dldir does exist
#         # check if gtest tar is already there
#         if [ -f "$DL_DIR/`basename $GTEST_URL`" ]; then
#             # it is there!
#             echo "Found $DL_DIR/`basename $GTEST_URL`"
#         else
#             # it's not... download
#             echo "Downloading gtest..."
#             wget --no-check-certificate -P "$DL_DIR" "$GTEST_URL" #>> "$LOGFILE" 2>&1
#         fi
#     fi

#     cd $DL_DIR
#     # extract zip
#     echo "Extracting in $DL_DIR..."
#     #cd "$PROJECT_ROOT_DIR/include/"
#     tar -zxvf "$DL_DIR/$GTEST_TAR_FILENAME" #>> "$LOGFILE" 2>&1

#     # build
#     echo "Building..."
#     #cd "$GTEST_INSTALL_DIR"
#     if [ ! -d "$DL_DIR/build" ]; then
#         mkdir build
#     fi
#     cd build
#     cmake -DBUILD_SHARED_LIBS=ON \
#           -DBUILD_STATIC_LIBS=ON \
#           -DCMAKE_INSTALL_PREFIX="$PROJECT_ROOT_DIR/local" ../gtest-2.1.1/.
#     make -j${CORES}
#     make install

#     # links cmake files into share/cmake
#     cd $PROJECT_ROOT_DIR
#     ln -s local/lib/cmake/gtest share/cmake/gtest

#     echo "Done Installing gtest!"
# fi

exit 0
