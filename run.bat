@echo off

cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -Wno-dev

make -C build
