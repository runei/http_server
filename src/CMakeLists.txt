add_library(Calculator STATIC Calculator.cpp)

target_include_directories(Calculator PUBLIC ${CMAKE_SOURCE_DIR}/include)
