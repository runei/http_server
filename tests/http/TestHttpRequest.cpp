#include "CppUTest/TestHarness.h"

#include "HttpRequest.hpp"
#include "Method.hpp"
#include "SocketException.hpp"

TEST_GROUP (HttpRequestTest)
{
    void setup() override {}
    void teardown() override {}
};

TEST (HttpRequestTest, ConstructHttpRequestWithValidMethodAndUrl)
{
    // Arrange
    Method           method = Method::Get;
    std::string_view url    = "/index.html";

    // Act
    HttpRequest request = HttpRequest::Builder().setMethod(method).setUrl(url).build();

    // Assert
    CHECK(method == request.getMethod());
    STRCMP_EQUAL(url.data(), request.getUrl().data());
}

TEST (HttpRequestTest, GetHeaderReturnsNulloptIfHeaderIsNotFound)
{
    // Arrange
    HttpRequest request = HttpRequest::Builder().setMethod(Method::Get).setUrl("/index.html").build();

    // Act
    std::optional<std::string_view> missing_header = request.getHeader("NonExistentHeader");

    // Assert
    CHECK_FALSE(missing_header.has_value());
}

TEST (HttpRequestTest, ConstructHttpRequestWithMultipleHeaders)
{
    // Arrange
    Method           method = Method::Post;
    std::string_view url    = "/submit";

    // Act
    HttpRequest request = HttpRequest::Builder()
                              .setMethod(method)
                              .setUrl(url)
                              .addHeader("Content-Type", "application/json")
                              .addHeader("Authorization", "Bearer token")
                              .build();

    // Assert
    auto content_type = request.getHeader("Content-Type");
    CHECK(content_type.has_value());
    STRCMP_EQUAL("application/json", content_type->data());

    auto authorization = request.getHeader("Authorization");
    CHECK(authorization.has_value());
    STRCMP_EQUAL("Bearer token", authorization->data());
}
