#!/usr/bin/env bash

set -e

export CMAKE_INSTALL_PREFIX=${CMAKE_BUILD_DIR}/_install

echo "Configure"
mkdir -p ${CMAKE_BUILD_DIR}
cmake -B${CMAKE_BUILD_DIR} -H. -G "Unix Makefiles" \
      -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} \
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
      -DLIGHTCXX_ENABLE_TESTS=ON

echo "Build"
make -C ${CMAKE_BUILD_DIR}

echo "Run tests"
make -C ${CMAKE_BUILD_DIR} test
