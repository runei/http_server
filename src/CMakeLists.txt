# add_subdirectory(server)
add_subdirectory(common)
add_subdirectory(http)
add_subdirectory(socket)
add_subdirectory(handlers)

add_executable(Main main.cpp)

target_link_libraries(
    Main
    PRIVATE SocketManager
            HttpResponse
            HttpStatusCode
)
