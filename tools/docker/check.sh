#!/usr/bin/env bash

set -e

mkdir -p ./build/$1
cmake -G Ninja -H. -B./build/$1
cmake --build ./build/$1 --target build_all_tests
cd ./build/$1 && ctest --output-on-failure .
