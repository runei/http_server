add_subdirectory(socket)
add_subdirectory(http)
add_subdirectory(common)
add_subdirectory(handlers)
add_subdirectory(server)

add_library(
    Client
    STATIC
    Client.cpp
)

target_include_directories(Client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Client PUBLIC Definitions)
