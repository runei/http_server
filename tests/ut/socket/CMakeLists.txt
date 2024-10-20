# SocketManager
add_executable(
    TestSocketManager
    TestSocketManager.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestSocketManager
    PRIVATE SocketManager
            SocketException
            CppUTest
            CppUTestExt
)

add_test(NAME TestSocketManager COMMAND TestSocketManager)
