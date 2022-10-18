#!/usr/bin/env bash

export CC=gcc
export CXX=g++
export CMAKE_BUILD_TYPE=Debug
export CMAKE_BUILD_DIR=.build/ubuntu-gcc-Debug
./scripts/check.sh
