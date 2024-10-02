#pragma once

#include "HttpRequest.hpp"
#include "HttpStatusCode.hpp"
#include "HttpVersion.hpp"
#include "Result.hpp"

static constexpr size_t NumOfElementsInRequestLine = 3;

using RequestLine         = std::array<std::string, NumOfElementsInRequestLine>;
using RequestParserResult = Result<HttpRequest>;

class RequestParser
{
public:
    [[nodiscard]] static RequestParserResult parse(const std::string& raw_request);

private:
    static RequestLine extractRequestLine(const std::string& raw_request);
    static Method      extractMethod(const RequestLine& request_line);
    static std::string extractUrl(const RequestLine& request_line);
    static HttpVersion extractHttpVersion(const RequestLine& request_line);
    static HttpHeaders extractHeaders(const std::string& raw_request);
    static std::string trim(const std::string& str);
};
