#!/usr/bin/env bash

set -e
mkdir -p local
deno run --allow-env --allow-read --unstable tools/parse-std/walk-tests-dir.ts tests > local/local.txt
diff -U0 local/local.txt tools/parse-std/all-sections.txt > local/diff.txt
