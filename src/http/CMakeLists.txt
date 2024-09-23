add_library(
    HttpRequest
    STATIC
    HttpRequest.cpp
)

target_include_directories(HttpRequest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HttpRequest PUBLIC SocketException)
