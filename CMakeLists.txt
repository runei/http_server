cmake_minimum_required(VERSION 3.20)

project(Calculator)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

# Unit test coverage flags
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message("Enabling coverage options")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_subdirectory(src)
add_subdirectory(tests)
