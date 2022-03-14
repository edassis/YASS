@echo off

@REM cmake -G "Unix Makefiles" -B build -Wno-dev
cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -Wno-dev

@REM cmake --build build --config Debug --target all
cmake --build build -j 12
