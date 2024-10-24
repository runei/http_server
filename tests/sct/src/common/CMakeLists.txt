# Logger
add_library(
    Logger
    STATIC
    Logger.cpp
)

target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
