#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <string>

#include "HttpRequest.hpp"
#include "HttpStatusCode.hpp"
#include "HttpVersion.hpp"
#include "Method.hpp"
#include "RequestParser.hpp"

TEST_GROUP (RequestParserTest)
{
};

TEST (RequestParserTest, ParseValidGetRequest)
{
    // Arrange
    const std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";

    // Act
    const auto result = RequestParser::parse(raw_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::OK, result.status());

    const auto http_request = result.value();
    LONGS_EQUAL(Method::Get, http_request.getMethod());
    STRCMP_EQUAL("/index.html", http_request.getUrl().data());
    LONGS_EQUAL(HttpVersion::Http11, http_request.getHttpVersion());

    const auto host = http_request.getHeader("Host");
    if (host.has_value())
    {
        STRCMP_EQUAL("localhost", host.value().data());
    }
    else
    {
        FAIL("Host has no value.");
    }
}

TEST (RequestParserTest, ParseInvalidMethod)
{
    // Arrange
    const std::string raw_request = "INVALID /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";

    // Act
    const auto result = RequestParser::parse(raw_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::MethodNotAllowed, result.status());
}

TEST (RequestParserTest, ParseUnsupportedHttpVersion)
{
    // Arrange
    const std::string raw_request = "GET /index.html HTTP/2.0\r\nHost: localhost\r\n\r\n";

    // Act
    const auto result = RequestParser::parse(raw_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::HttpVersionNotSupported, result.status());
}

TEST (RequestParserTest, ParseMissingHeaders)
{
    // Arrange
    const std::string raw_request = "GET /index.html HTTP/1.1\r\n\r\n";

    // Act
    const auto result = RequestParser::parse(raw_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::BadRequest, result.status());
}

TEST (RequestParserTest, ParseValidPostRequest)
{
    // Arrange
    const std::string raw_request = "POST /submit-form HTTP/1.1\r\nHost: localhost\r\nContent-Length: 0\r\n\r\n";

    // Act
    const auto result = RequestParser::parse(raw_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::OK, result.status());

    const auto http_request = result.value();
    LONGS_EQUAL(Method::Post, http_request.getMethod());
    STRCMP_EQUAL("/submit-form", http_request.getUrl().data());
    LONGS_EQUAL(HttpVersion::Http11, http_request.getHttpVersion());

    const auto host = http_request.getHeader("Host");
    if (host.has_value())
    {
        STRCMP_EQUAL("localhost", host.value().data());
    }
    else
    {
        FAIL("Host has no value.");
    }

    const auto content = http_request.getHeader("Content-Length");
    if (content.has_value())
    {
        STRCMP_EQUAL("0", content.value().data());
    }
    else
    {
        FAIL("Content-Length has no value.");
    }
}
