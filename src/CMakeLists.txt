# add_subdirectory(handlers)  add_subdirectory(server)
add_subdirectory(exceptions)
add_subdirectory(http)
add_subdirectory(socket)

add_executable(Main main.cpp)

target_link_libraries(Main PRIVATE SocketManager)
