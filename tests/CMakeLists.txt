# SocketManager
add_executable(
    TestSocketManager
    TestSocketManager.cpp
    main.cpp
)

target_link_libraries(
    TestSocketManager
    PRIVATE SocketManager
            SocketException
            CppUTest
            CppUTestExt
)

add_test(NAME TestSocketManager COMMAND TestSocketManager)

# SocketException
add_executable(
    TestSocketException
    TestSocketException.cpp
    main.cpp
)

target_link_libraries(
    TestSocketException
    PRIVATE SocketException
            CppUTest
            CppUTestExt
)

add_test(NAME TestSocketException COMMAND TestSocketException)

# HttpRequest
add_executable(
    TestHttpRequest
    TestHttpRequest.cpp
    main.cpp
)

target_link_libraries(
    TestHttpRequest
    PRIVATE HttpRequest
            SocketException
            CppUTest
            CppUTestExt
)

add_test(NAME TestHttpRequest COMMAND TestHttpRequest)
