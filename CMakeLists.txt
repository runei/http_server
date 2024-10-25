cmake_minimum_required(VERSION 3.20)

project(HTTPServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -Wall -Wextra -pedantic -Werror")
set(CMAKE_TEST_MAIN "${CMAKE_SOURCE_DIR}/tests/ut/main.cpp")

add_compile_definitions(STATIC_DIR_PATH="${CMAKE_SOURCE_DIR}/static/")

enable_testing()

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Release flags (optimizations, no debug symbols)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building in Release mode with optimizations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif()

# Debug flags (no optimizations, debug symbols)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building in Debug mode with debug symbols")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fsanitize=address -fsanitize=undefined")
endif()

# Unit test coverage flags
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message("Enabling coverage options")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

if (NOT BUILD_SCT)
    add_subdirectory(src)
    add_subdirectory(tests/ut)
else ()
    add_subdirectory(tests/sct)
endif()
