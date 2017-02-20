#!/bin/sh
mkdir -p build
cd build
cmake -G 'CodeBlocks - Unix Makefiles' -D CMAKE_BUILD_TYPE=Debug ..
