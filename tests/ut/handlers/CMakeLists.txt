# FileRequestHandler
add_executable(
    TestFileRequestHandler
    TestFileRequestHandler.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestFileRequestHandler
    PRIVATE FileRequestHandler
            HttpRequest
            HttpResponse
            CppUTest
            CppUTestExt
)

add_test(NAME TestFileRequestHandler COMMAND TestFileRequestHandler)

# RequestDispatcher
add_executable(
    TestRequestDispatcher
    TestRequestDispatcher.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestRequestDispatcher
    PRIVATE RequestDispatcher
            IRequestHandler
            Definitions
            CppUTest
            CppUTestExt
)

add_test(NAME TestRequestDispatcher COMMAND TestRequestDispatcher)
