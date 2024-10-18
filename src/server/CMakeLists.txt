add_library(
    Server
    STATIC
    Server.cpp
)

target_include_directories(Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    Server
    PUBLIC RequestDispatcher
           SocketManager
           FileRequestHandler
)
