@echo off

cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug

cd build

make
