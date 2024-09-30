#include "CppUTest/TestHarness.h"

#include "HttpRequest.hpp"
#include "RequestParser.hpp"

TEST_GROUP (RequestParserTest)
{
};

TEST (RequestParserTest, ParseValidGetRequest)
{
    // Arrange
    std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpRequest http_request;

    // Act
    HttpStatusCode status = RequestParser::parse(raw_request, http_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::OK, status);
    LONGS_EQUAL(Method::Get, http_request.getMethod());
    STRCMP_EQUAL("/index.html", http_request.getUrl().data());
    LONGS_EQUAL(HttpVersion::Http11, http_request.getHttpVersion());
    STRCMP_EQUAL("localhost", http_request.getHeader("Host").value().data());
}

TEST (RequestParserTest, ParseInvalidMethod)
{
    // Arrange
    std::string raw_request = "INVALID /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    HttpRequest http_request;

    // Act
    HttpStatusCode status = RequestParser::parse(raw_request, http_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::MethodNotAllowed, status);
}

TEST (RequestParserTest, ParseUnsupportedHttpVersion)
{
    // Arrange
    std::string raw_request = "GET /index.html HTTP/2.0\r\nHost: localhost\r\n\r\n";
    HttpRequest http_request;

    // Act
    HttpStatusCode status = RequestParser::parse(raw_request, http_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::HttpVersionNotSupported, status);
}

TEST (RequestParserTest, ParseMissingHeaders)
{
    // Arrange
    std::string raw_request = "GET /index.html HTTP/1.1\r\n\r\n";
    HttpRequest http_request;

    // Act
    HttpStatusCode status = RequestParser::parse(raw_request, http_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::BadRequest, status);
}

TEST (RequestParserTest, ParseValidPostRequest)
{
    // Arrange
    std::string raw_request = "POST /submit-form HTTP/1.1\r\nHost: localhost\r\nContent-Length: 0\r\n\r\n";
    HttpRequest http_request;

    // Act
    HttpStatusCode status = RequestParser::parse(raw_request, http_request);

    // Assert
    LONGS_EQUAL(HttpStatusCode::OK, status);
    LONGS_EQUAL(Method::Post, http_request.getMethod());
    STRCMP_EQUAL("/submit-form", http_request.getUrl().data());
    LONGS_EQUAL(HttpVersion::Http11, http_request.getHttpVersion());
    STRCMP_EQUAL("localhost", http_request.getHeader("Host").value().data());
    STRCMP_EQUAL("0", http_request.getHeader("Content-Length").value().data());
}
