# TestCaseResult
add_library(
    TestCaseResult
    STATIC
    TestCaseResult.cpp
)

target_include_directories(TestCaseResult PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestCaseResult PUBLIC Logger)

# TestGroup
add_library(
    TestGroup
    STATIC
    TestGroup.cpp
)

target_include_directories(TestGroup PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    TestGroup
    PUBLIC TestCaseResult
           Logger
           TestCase
)

# TestRunner
add_library(
    TestRunner
    STATIC
    TestRunner.cpp
)

target_include_directories(TestRunner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    TestRunner
    PUBLIC TestCaseResult
           Logger
           TestGroup
)
