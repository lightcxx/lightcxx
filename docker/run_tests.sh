#!/usr/bin/env bash

set -e

cmake -H/code -B/code/build-docker-$1
cd /code/build-docker-$1
make -j8 check
