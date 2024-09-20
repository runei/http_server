add_executable( TestSocketManager TestSocketManager.cpp main.cpp )

target_link_libraries( TestSocketManager PRIVATE SocketManager SocketException CppUTest CppUTestExt
)

add_test(NAME TestSocketManager COMMAND TestSocketManager)
