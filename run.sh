#!/usr/bin/env bash
set -e  # stop on first error

# Make build directory if it doesn't exist
mkdir -p build
cd build

# Generate build files (only needed first time or after changes to CMakeLists.txt)
cmake -G Ninja ..

# Build the project
ninja

# Run the program
./CPPP
