cmake_minimum_required(VERSION 3.20)

project(HTTPServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
set(CMAKE_TEST_MAIN "${CMAKE_SOURCE_DIR}/tests/ut/main.cpp")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_compile_definitions(
    STATIC_DIR_PATH="${CMAKE_SOURCE_DIR}/static/"
    CPPUTEST_MEM_LEAK_DETECTION_DISABLED
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building in Release mode with optimizations")
    add_compile_options(-O3 -DNDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building in Debug mode with debug symbols")
    add_compile_options(-g -O0 -fsanitize=address -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message("Enabling coverage options")
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(--coverage)
endif()

# Option to build system tests
option(BUILD_SCT "Build system tests" OFF)

if(NOT BUILD_SCT)
    add_subdirectory(src)
    add_subdirectory(tests/ut)
else()
    add_subdirectory(tests/sct)
endif()
