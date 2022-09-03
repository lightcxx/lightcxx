#!/usr/bin/env bash

export CC=gcc
export CXX=g++
export CMAKE_BUILD_TYPE=Release
export CMAKE_BUILD_DIR=.build/ubuntu-gcc-Release
./tools/scripts/check.sh
