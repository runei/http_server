#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <string_view>

#include "HttpResponse.hpp"
#include "HttpStatusCode.hpp"
#include "HttpVersion.hpp"

TEST_GROUP (HttpResponseTest)
{
};

TEST (HttpResponseTest, BuildFullHttpResponse)
{
    // Arrange
    HttpResponse::Builder  builder;
    const std::string_view expected =
        "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hello, World!</body></html>";

    // Act
    const auto response = builder.setHttpVersion(HttpVersion::Http11)
                              .setStatusCode(HttpStatusCode::OK)
                              .addHeader("Content-Type", "text/html")
                              .setBody("<html><body>Hello, World!</body></html>")
                              .build();
    const auto actual = response.buildResponse();

    // Assert
    STRCMP_EQUAL(expected.data(), actual.data());
}
