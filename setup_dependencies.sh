#!/usr/bin/env bash

set -e

mkdir -p .downloads
rm -rf .downloads
mkdir -p .downloads
echo "Downloading libc++ source code..."
wget -O .downloads/libcxx.tar.xz https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.0/libcxx-14.0.0.src.tar.xz
echo "Downloading libc++abi source code..."
wget -O .downloads/libcxxabi.tar.xz https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.0/libcxxabi-14.0.0.src.tar.xz

echo "Decompressing libcxx into third_party directory..."
rm -rf third_party/libcxx
tar -xf .downloads/libcxx.tar.xz -C .downloads
mv .downloads/libcxx-14.0.0.src third_party/libcxx

echo "Decompressing libcxx into third_party directory..."
rm -rf third_party/libcxxabi
tar -xf .downloads/libcxxabi.tar.xz -C .downloads
mv .downloads/libcxxabi-14.0.0.src third_party/libcxxabi

echo "Removing temporary .downloads directory..."
rm -rf .downloads
echo "Done."
