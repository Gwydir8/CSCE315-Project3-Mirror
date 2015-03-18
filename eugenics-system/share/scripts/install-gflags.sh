#!/bin/bash
# install gflags
# USAGE: cd $PROJECT_ROOT; ./install-gflags.sh

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

# GFLAGS_URL="https://github.com/schuhschuh/gflags/archive/v2.1.1.tar.gz"
# if [ "$UNAME" = "Darwin" ]; then
#     GFLAGS_TAR_FILENAME="`basename $GFLAGS_URL`"
# else
#     GFLAGS_TAR_FILENAME="`basename $GFLAGS_URL .tar.gz`"
# fi
GFLAGS_INSTALL_DIR="$PROJECT_SYSTEM_DIR/include/gflags-2.1.1"

echo "Checking if you have gflags..."
if [ -d "$GFLAGS_INSTALL_DIR" ]; then
    echo "You have gflags."
else
    # if you don't have gflags
    echo "You don't have gflags"

    cd $PROJECT_SYSTEM_DIR/..
    git submodule update --init
    echo "Pulling Gflags 2.1.1"
    cd $PROJECT_SYSTEM_DIR
    cd libraries
    cd gflags
    cmake -DBUILD_SHARED_LIBS=ON \
          -DBUILD_STATIC_LIBS=ON \
          -DCMAKE_INSTALL_PREFIX="$PROJECT_SYSTEM_DIR/local" ../gflags-2.1.1/.
    make -j${CORES}
    make install



    echo "Done Installing gflags!"
fi

# echo "Checking if you have gflags..."
# if [ -d "$GFLAGS_INSTALL_DIR" ]; then
#     echo "You have gflags."
# else
#     # if you don't have gflags
#     echo "You don't have gflags"

#     # download if you don't have it
#     if [ ! -d "$DL_DIR" ]; then
#         # if dldir doesn't exist create it
#         mkdir -p "$DL_DIR"
#         # download gflags
#         echo "Downloading gflags"
#         wget --no-check-certificate -P "$DL_DIR" "$GFLAGS_URL" #>> "$LOGFILE" 2>&1
#     else
#         # dldir does exist
#         # check if gflags tar is already there
#         if [ -f "$DL_DIR/`basename $GFLAGS_URL`" ]; then
#             # it is there!
#             echo "Found $DL_DIR/`basename $GFLAGS_URL`"
#         else
#             # it's not... download
#             echo "Downloading gflags..."
#             wget --no-check-certificate -P "$DL_DIR" "$GFLAGS_URL" #>> "$LOGFILE" 2>&1
#         fi
#     fi

#     cd $DL_DIR
#     # extract zip
#     echo "Extracting in $DL_DIR..."
#     #cd "$PROJECT_ROOT_DIR/include/"
#     tar -zxvf "$DL_DIR/$GFLAGS_TAR_FILENAME" #>> "$LOGFILE" 2>&1

#     # build
#     echo "Building..."
#     #cd "$GFLAGS_INSTALL_DIR"
#     if [ ! -d "$DL_DIR/build" ]; then
#         mkdir build
#     fi
#     cd build
#     cmake -DBUILD_SHARED_LIBS=ON \
#           -DBUILD_STATIC_LIBS=ON \
#           -DCMAKE_INSTALL_PREFIX="$PROJECT_ROOT_DIR/local" ../gflags-2.1.1/.
#     make -j${CORES}
#     make install

#     # links cmake files into share/cmake
#     cd $PROJECT_ROOT_DIR
#     ln -s local/lib/cmake/gflags share/cmake/gflags

#     echo "Done Installing gflags!"
# fi

exit 0
