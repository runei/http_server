# Server
add_executable(
    TestServer
    TestServer.cpp
    ${CMAKE_TEST_MAIN}
)

target_link_libraries(
    TestServer
    PRIVATE Server
            Client
            CppUTest
            CppUTestExt
)

add_test(NAME TestServer COMMAND TestServer)
