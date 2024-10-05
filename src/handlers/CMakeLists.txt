# ErrorHandler
add_library(
    ErrorHandler
    STATIC
    ErrorHandler.cpp
)

target_include_directories(ErrorHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    ErrorHandler
    PUBLIC HttpStatusCode
           HttpResponse
)

# FileResponseHandler
add_library(
    FileResponseHandler
    STATIC
    FileResponseHandler.cpp
)

target_include_directories(
    FileResponseHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    FileResponseHandler
    PUBLIC HttpStatusCode
           HttpResponse
           CommonFunctions
           ErrorHandler
)
