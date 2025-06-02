#!/usr/bin/env bash

set -euo pipefail

BUILD_TYPE="Debug"  # Default
while [[ $# -gt 0 ]]; do
  case "$1" in
    -r|--release)
      BUILD_TYPE="Release"
      shift
      ;;
    -d|--debug)
      BUILD_TYPE="Debug"
      shift
      ;;
    *)
      echo "Usage: $0 [-r|--release] [-d|--debug]" >&2
      exit 1
      ;;
  esac
done

# Directory for out‑of‑source build
BUILD_DIR="build"

# Create it if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p "$BUILD_DIR"
fi

# Enter the build directory
cd "$BUILD_DIR"

# Configure with Clang/Clang++
cmake \
  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  ..

echo
echo "Configuration complete. To build, run:"
echo "  cmake --build ."
