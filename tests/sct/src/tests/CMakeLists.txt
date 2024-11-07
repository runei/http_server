# TestCase
add_library(
    TestCase
    STATIC
    TestCase.cpp
)

target_include_directories(TestCase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    TestCase
    PUBLIC Result
           Logger
)
