#include "CppUTest/TestHarness.h"

#include "HttpRequest.hpp"
#include "SocketException.hpp"

TEST_GROUP (HttpRequestTest)
{
    void setup() override {}
    void teardown() override {}
};

TEST (HttpRequestTest, ConstructHttpRequestWithValidMethodAndUrl)
{
    // Arrange
    std::string_view method = "GET";
    std::string_view url    = "/index.html";

    // Act
    HttpRequest request = HttpRequest::Builder().setMethod(method).setUrl(url).build();

    // Assert
    STRCMP_EQUAL(method.data(), request.getMethod().data());
    STRCMP_EQUAL(url.data(), request.getUrl().data());
}

TEST (HttpRequestTest, AddHeadersToHttpRequestAndRetrieveThem)
{
    // Arrange
    std::string_view method       = "GET";
    std::string_view url          = "/index.html";
    std::string_view header_key   = "Accept";
    std::string_view header_value = "text/html";

    // Act
    HttpRequest request =
        HttpRequest::Builder().setMethod(method).setUrl(url).addHeader(header_key, header_value).build();

    // Assert
    std::optional<std::string_view> retrieved_header = request.getHeader(header_key);
    CHECK(retrieved_header.has_value());
    STRCMP_EQUAL(header_value.data(), retrieved_header->data());
}

TEST (HttpRequestTest, GetHeaderReturnsNulloptIfHeaderIsNotFound)
{
    // Arrange
    HttpRequest request = HttpRequest::Builder().setMethod("GET").setUrl("/index.html").build();

    // Act
    std::optional<std::string_view> missing_header = request.getHeader("NonExistentHeader");

    // Assert
    CHECK_FALSE(missing_header.has_value());
}

TEST (HttpRequestTest, ThrowExceptionIfMethodOrUrlIsMissing)
{
    // Arrange-Act-Assert
    CHECK_THROWS(SocketException, HttpRequest::Builder().setUrl("/index.html").build());
    CHECK_THROWS(SocketException, HttpRequest::Builder().setMethod("GET").build());
}

TEST (HttpRequestTest, ConstructHttpRequestWithMultipleHeaders)
{
    // Arrange
    std::string_view method = "POST";
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
