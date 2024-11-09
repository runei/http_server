# MockTestCase
add_library(
    MockTestCase
    STATIC
    MockTestCase.cpp
)

target_include_directories(MockTestCase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(MockTestCase PUBLIC TestCase)

# TestCase
add_executable(
    TestTestCase
    TestTestCase.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestTestCase
    PRIVATE TestCase
            TestCaseResult
            MockTestCase
            CppUTest
            CppUTestExt
)

add_test(NAME TestTestCase COMMAND TestTestCase)
