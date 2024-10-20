#include "CppUTest/TestHarness.h"

#include <string>

#include "FileRequestHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

TEST_GROUP (FileRequestHandlerTests)
{
};

TEST (FileRequestHandlerTests, HandleRequest_Returns200OnValidFile)
{
    // Arrange
    HttpRequest request =
        HttpRequest::Builder().setMethod(Method::Get).setUrl("test.html").setHttpVersion(HttpVersion::Http11).build();

    std::string expected =
        "HTTP/1.1 200 OK\nContent-Length: 40\nContent-Type: text/html\n\n<html><body>Hello, World!</body></html>\n";

    // Act
    FileRequestHandler request_handler;
    HttpResponse       response = request_handler.handle(request);

    // Assert
    STRCMP_EQUAL(expected.data(), response.buildResponse().data());
}

TEST (FileRequestHandlerTests, HandleRequest_Returns404OnFileNotFound)
{
    // Arrange
    HttpRequest request = HttpRequest::Builder()
                              .setMethod(Method::Get)
                              .setUrl("test_not_found.html")
                              .setHttpVersion(HttpVersion::Http11)
                              .build();
    std::string expected =
        "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<html><head><title>404 Not "
        "Found</title></head><body><h1>404 Not Found</h1><p>An error occurred: 404 Not Found</p></body></html>";

    // Act
    FileRequestHandler request_handler;
    HttpResponse       response = request_handler.handle(request);

    // Assert
    STRCMP_EQUAL(expected.data(), response.buildResponse().data());
}
