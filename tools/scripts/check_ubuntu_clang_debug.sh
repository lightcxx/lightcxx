#!/usr/bin/env bash

export CC=clang
export CXX=clang++
export CMAKE_BUILD_TYPE=Debug
export CMAKE_BUILD_DIR=.build/ubuntu-clang-Debug
./tools/scripts/check.sh
