# TestSuite
add_executable(
    TestTestSuite
    TestTestSuite.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestTestSuite
    PRIVATE TestSuite
            TestCaseResult
            MockTestCase
            CppUTest
            CppUTestExt
)

add_test(NAME TestTestSuite COMMAND TestTestSuite)
