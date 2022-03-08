#!/bin/sh
cc='gcc'
cxx='g++'

if [[ $OSTYPE == 'darwin'* ]]; then
    cc='gcc-11'
    cxx='g++-11'
fi

# Create build files
cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$cc -DCMAKE_CXX_COMPILER=$cxx -Wno-dev
# cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -Wno-dev

# Build
cmake --build build