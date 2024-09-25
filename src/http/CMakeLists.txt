add_library(
    HttpRequest
    STATIC
    HttpRequest.cpp
)

target_include_directories(HttpRequest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HttpRequest PUBLIC SocketException)

add_library(
    HttpStatusCode
    STATIC
    HttpStatusCode.cpp
)

target_include_directories(HttpStatusCode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HttpStatusCode PUBLIC SocketException)
