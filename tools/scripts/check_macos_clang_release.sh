#!/usr/bin/env bash

export CC=clang
export CXX=clang++
export CMAKE_BUILD_TYPE=Release
export CMAKE_BUILD_DIR=.build/Release
./tools/scripts/check.sh
