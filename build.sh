#!/usr/bin/env bash

set -euo pipefail

# Directory for out‑of‑source build
BUILD_DIR="build"

# Create it if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

# Enter the build directory
cd "$BUILD_DIR"

# Configure with Clang/Clang++
cmake \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  ..

echo
echo "Configuration complete. To build, run:"
echo "  cmake --build ."
