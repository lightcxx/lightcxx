#!/usr/bin/env bash

set -e

mkdir -p ./build/$1
cmake -G Ninja -H. -B./build/$1
cmake --build ./build/$1 --target check
