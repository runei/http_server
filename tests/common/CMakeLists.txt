# SocketException
add_executable(
    TestSocketException
    TestSocketException.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestSocketException
    PRIVATE SocketException
            CppUTest
            CppUTestExt
)

add_test(NAME TestSocketException COMMAND TestSocketException)
