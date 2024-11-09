# TestCaseResult
add_library(
    TestCaseResult
    STATIC
    TestCaseResult.cpp
)

target_include_directories(TestCaseResult PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestCaseResult PUBLIC Logger)

# TestSuite
add_library(
    TestSuite
    STATIC
    TestSuite.cpp
)

target_include_directories(TestSuite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    TestSuite
    PUBLIC TestCaseResult
           Logger
           TestCase
)
