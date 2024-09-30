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

# HttpResponse
add_executable(
    TestHttpResponse
    TestHttpResponse.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestHttpResponse
    PRIVATE HttpResponse
            HttpStatusCode
            CppUTest
            CppUTestExt
)

add_test(NAME TestHttpResponse COMMAND TestHttpResponse)

# RequestParser
add_executable(
    TestRequestParser
    TestRequestParser.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestRequestParser
    PRIVATE RequestParser
            HttpStatusCode
            CppUTest
            CppUTestExt
)

add_test(NAME TestRequestParser COMMAND TestRequestParser)
