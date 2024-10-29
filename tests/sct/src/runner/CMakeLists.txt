# Result
add_library(
    Result
    STATIC
    Result.cpp
)

target_include_directories(Result PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Result PUBLIC Logger)
