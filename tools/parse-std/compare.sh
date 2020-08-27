#!/usr/bin/env bash

set -e
mkdir -p local
deno run --allow-read --unstable tools/parse-std/walk-tests-dir.ts tests > local/local.txt
deno run --allow-net tools/parse-std/parse-from-timsong-cpp-github-io.ts > local/remote.txt
diff local/local.txt local/remote.txt > local/diff.txt
