#include "CppUTest/TestHarness.h"

#include "HttpRequest.hpp"
#include "HttpVersion.hpp"
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
    Method           method       = Method::Get;
    std::string_view url          = "/index.html";
    HttpVersion      http_version = HttpVersion::Http11;

    // Act
    HttpRequest request = HttpRequest::Builder().setMethod(method).setUrl(url).setHttpVersion(http_version).build();

    // Assert
    LONGS_EQUAL(method, request.getMethod());
    STRCMP_EQUAL(url.data(), request.getUrl().data());
    LONGS_EQUAL(http_version, request.getHttpVersion());
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
    Method           method       = Method::Post;
    std::string_view url          = "/submit";
    HttpVersion      http_version = HttpVersion::Http11;

    // Act
    HttpRequest request = HttpRequest::Builder()
                              .setMethod(method)
                              .setUrl(url)
                              .setHttpVersion(http_version)
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
