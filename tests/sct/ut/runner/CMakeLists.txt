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
