# HttpRequest
add_executable(
    TestHttpRequest
    TestHttpRequest.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestHttpRequest
    PRIVATE HttpRequest
            SocketException
            CppUTest
            CppUTestExt
)

add_test(NAME TestHttpRequest COMMAND TestHttpRequest)
