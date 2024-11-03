#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <optional>
#include <string>
#include <string_view>

#include "HttpRequest.hpp"
#include "HttpVersion.hpp"
#include "Method.hpp"

TEST_GROUP (HttpRequestTest)
{
    void setup() override {}
    void teardown() override {}
};

TEST (HttpRequestTest, ConstructHttpRequestWithValidMethodAndUrl)
{
    // Arrange
    const Method      method       = Method::Get;
    const std::string url          = "/index.html";
    const HttpVersion http_version = HttpVersion::Http11;

    // Act
    const HttpRequest request =
        HttpRequest::Builder().setMethod(method).setUrl(url).setHttpVersion(http_version).build();

    // Assert
    LONGS_EQUAL(method, request.getMethod());
    STRCMP_EQUAL(url.c_str(), request.getUrl().c_str());
    LONGS_EQUAL(http_version, request.getHttpVersion());
}

TEST (HttpRequestTest, GetHeaderReturnsNulloptIfHeaderIsNotFound)
{
    // Arrange
    const HttpRequest request = HttpRequest::Builder().setMethod(Method::Get).setUrl("/index.html").build();

    // Act
    const std::optional<std::string_view> missing_header = request.getHeader("NonExistentHeader");

    // Assert
    CHECK_FALSE(missing_header.has_value());
}

TEST (HttpRequestTest, ConstructHttpRequestWithMultipleHeaders)
{
    // Arrange
    const Method      method       = Method::Post;
    const std::string url          = "/submit";
    const HttpVersion http_version = HttpVersion::Http11;

    // Act
    const HttpRequest request = HttpRequest::Builder()
                                    .setMethod(method)
                                    .setUrl(url)
                                    .setHttpVersion(http_version)
                                    .addHeader("Content-Type", "application/json")
                                    .addHeader("Authorization", "Bearer token")
                                    .build();

    // Assert
    const auto content_type = request.getHeader("Content-Type");
    if (content_type.has_value())
    {
        STRCMP_EQUAL("application/json", content_type->data());
    }
    else
    {
        FAIL("Content-Type has no value.");
    }

    const auto authorization = request.getHeader("Authorization");
    if (authorization.has_value())
    {
        STRCMP_EQUAL("Bearer token", authorization->data());
    }
    else
    {
        FAIL("Authorization has no value.");
    }
}
