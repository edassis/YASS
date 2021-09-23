cmake_minimum_required(VERSION 3.10)

project(SDL_engine VERSION 0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")   # binary destination

set(src_dir "${PROJECT_SOURCE_DIR}/src")
file(GLOB src_files "${src_dir}/application/*.cpp" "${src_dir}/engine/*.cpp")

# message(src_dir="${src_dir}")
# message(src_files="${src_files}")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunreachable-code -pedantic -Wfloat-equal -ggdb -Og -DDEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wunreachable-code -pedantic -Wfloat-equal -Wconversion -ggdb -Og -DDEBUG")
endif()
# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#     target_compile_options( vector-test PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
# endif()
# if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
#     target_compile_options( vector-test PRIVATE /W3 /w44265 /w44061 /w44062 )
# endif()

if (MINGW) 
    # list(APPEND CMAKE_CXX_FLAGS_DEBUG "-mconsole")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mconsole")
endif()

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")

# includes
include_directories("include/")
include_directories("C:/dev/SDL2-mingw64/i686-w64-mingw32/include")

# SDL2 https://github.com/aminosbh/sdl2-cmake-modules
## Appends custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

set(SDL2_PATH "C:/dev/SDL2-mingw64/i686-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Executable
add_executable(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::Main SDL2::TTF SDL2::Image SDL2::Mixer)