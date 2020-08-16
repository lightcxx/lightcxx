#!/usr/bin/env bash

set -e

mkdir -p ./build/$1
cmake -H. -B./build/$1
cd ./build/$1
if [[ -z "${UPLOAD_TO_CDASH}" ]]; then
  make -j8 check_and_upload
else
  make -j8 check
fi
