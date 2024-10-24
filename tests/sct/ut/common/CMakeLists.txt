# Logger
add_executable(
    TestLogger
    TestLogger.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestLogger
    PRIVATE Logger
            CppUTest
            CppUTestExt
)

add_test(NAME TestLogger COMMAND TestLogger)
