#include "CppUTest/TestHarness.h"

#include "HttpResponse.hpp"
#include "HttpStatusCode.hpp"

TEST_GROUP (HttpResponseTest)
{
};

TEST (HttpResponseTest, BuildFullHttpResponse)
{
    // Arrange
    HttpResponse::Builder builder;
    std::string_view expected = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hello, World!</body></html>";

    // Act
    auto response = builder.setStatusCode(HttpStatusCode::OK)
                        .addHeader("Content-Type", "text/html")
                        .setBody("<html><body>Hello, World!</body></html>")
                        .build();
    auto actual = response.buildResponse();

    // Assert
    STRCMP_EQUAL(expected.data(), actual.data());
}
