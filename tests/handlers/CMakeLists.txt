# FileResponseHandler
add_executable(
    TestFileResponseHandler
    TestFileResponseHandler.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestFileResponseHandler
    PRIVATE FileResponseHandler
            HttpRequest
            HttpResponse
            CppUTest
            CppUTestExt
)

add_test(NAME TestFileResponseHandler COMMAND TestFileResponseHandler)
