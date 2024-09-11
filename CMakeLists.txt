cmake_minimum_required(VERSION 3.20)

project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
