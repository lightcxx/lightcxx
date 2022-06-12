#!/usr/bin/env bash

set -e

./setup_dependencies.sh

CHECK_TYPE=${1:-test}
CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Debug}"

export CMAKE_BUILD_DIR=.build/${CMAKE_BUILD_TYPE}
export CMAKE_INSTALL_DIR=${CMAKE_BUILD_DIR}/_install

echo "\nConfigure\n"
mkdir -p ${CMAKE_BUILD_DIR}
cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_DIR} \
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
      -DLIGHTCXX_ENABLE_TESTS=ON \
      -G "Unix Makefiles" -B${CMAKE_BUILD_DIR} -H.
cd ${CMAKE_BUILD_DIR}

echo "\nBuild\n"
make -j8

echo "\nRun tests\n"
ctest

echo "\nInstall locally\n"
make install
