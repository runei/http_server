# HttpRequest
add_library(
    HttpRequest
    STATIC
    HttpRequest.cpp
)

target_include_directories(HttpRequest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HttpRequest PUBLIC SocketException)

# HttpStatusCode
add_library(
    HttpStatusCode
    STATIC
    HttpStatusCode.cpp
)

target_include_directories(HttpStatusCode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HttpStatusCode PUBLIC SocketException)

# HttpResponse
add_library(
    HttpResponse
    STATIC
    HttpResponse.cpp
)

target_include_directories(HttpResponse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    HttpResponse
    PUBLIC SocketException
           Definitions
)

# Method
add_library(
    Method
    INTERFACE
)

target_include_directories(Method INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    Method
    INTERFACE HttpStatusCode
)
