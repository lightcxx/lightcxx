#!/usr/bin/env bash

set -e
mkdir -p local
ls -R tests | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//  /g' | sed -e 's/^  \( *\)/\1[/' -e 's/$/]/' > local/local.txt
diff local/local.txt tools/parse-std/all-sections.txt > local/diff.txt
