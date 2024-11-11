# TestGroup
add_executable(
    TestTestGroup
    TestTestGroup.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestTestGroup
    PRIVATE TestGroup
            TestCaseResult
            MockTestCase
            CppUTest
            CppUTestExt
)

add_test(NAME TestTestGroup COMMAND TestTestGroup)

# TestRunner
add_executable(
    TestTestRunner
    TestTestRunner.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestTestRunner
    PRIVATE TestRunner
            TestCaseResult
            MockTestCase
            Logger
            CppUTest
            CppUTestExt
)

add_test(NAME TestTestRunner COMMAND TestTestRunner)
