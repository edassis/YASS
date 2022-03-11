include(CMakePrintHelpers)

cmake_minimum_required(VERSION 3.16.3)
project(SDL_engine VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")   # binary destination

set(src_dir "${PROJECT_SOURCE_DIR}/src")
set(header_dir "${PROJECT_SOURCE_DIR}/include")

file(
  GLOB src_files "${src_dir}/application/*.cpp" "${src_dir}/engine/*.cpp"
  "${header_dir}/application/*.h" "${header_dir}/engine/*.h"
)

# message(src_dir="${src_dir}")
# message(src_files="${src_files}")
# message(${CMAKE_CXX_COMPILER_ID})
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
  # target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunreachable-code -pedantic -Wfloat-equal -ggdb -Og -DDEBUG)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wno-unused-parameter -Wunreachable-code -pedantic -Wfloat-equal -Wconversion -ggdb -O0 -DDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_THREAD_SAFE")
endif()

# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#     target_compile_options( vector-test PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
# endif()
# if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
#     target_compile_options( vector-test PRIVATE /W3 /w44265 /w44061 /w44062 )
# endif()

if(MINGW)
  # list(APPEND CMAKE_CXX_FLAGS_DEBUG "-mconsole")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mconsole")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SDL2_PATH "C:/dev/SDL2-mingw64/i686-w64-mingw32")
endif()

# SDL2 https://github.com/aminosbh/sdl2-cmake-modules
## Appends custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Executable
add_executable(${PROJECT_NAME} ${src_files})
#target_include_directories(${PROJECT_NAME} PRIVATE "${header_dir}" "/opt/homebrew/include/SDL2" "${SDL2_PATH}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${SDL2_INCLUDE_DIRS}")
target_include_directories(${PROJECT_NAME} PRIVATE "${header_dir}")
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::Main SDL2::TTF SDL2::Image SDL2::Mixer)

# cmake_print_variables(INCLUDE_DIRECTORIES)
# cmake_print_properties(TARGETS ${PROJECT_NAME} PROPERTIES INCLUDE_DIRECTORIES)