#!/bin/sh
cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc-11 -DCMAKE_CXX_COMPILER=g++-11 -Wno-dev
cmake --build build

cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -Wno-dev

cmake --build build
