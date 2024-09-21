add_executable( TestSocketManager TestSocketManager.cpp main.cpp )

target_link_libraries( TestSocketManager PRIVATE SocketManager SocketException CppUTest CppUTestExt
)

add_test(NAME TestSocketManager COMMAND TestSocketManager)

add_executable( TestSocketException TestSocketException.cpp main.cpp )

target_link_libraries( TestSocketException PRIVATE SocketException CppUTest CppUTestExt
)

add_test(NAME TestSocketException COMMAND TestSocketException)
