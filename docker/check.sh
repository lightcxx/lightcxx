#!/usr/bin/env bash

set -e

mkdir -p ./build/$1
cmake -G Ninja -H. -B./build/$1
if [[ -z "${UPLOAD_TO_CDASH}" ]]; then
  cmake --build ./build/$1 --target check_and_upload
else
  cmake --build ./build/$1 --target check
fi
