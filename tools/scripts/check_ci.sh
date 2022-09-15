#!/usr/bin/env bash

set -e

./tools/scripts/setup_dependencies.sh

export CC=${1}
export CXX=${2}
export CMAKE_BUILD_TYPE="${3}"
export CMAKE_BUILD_DIR=.build/${CMAKE_BUILD_TYPE}
export CMAKE_INSTALL_PREFIX=${CMAKE_BUILD_DIR}/_install
./tools/scripts/check.sh
