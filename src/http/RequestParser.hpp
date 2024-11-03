#pragma once

#include <array>
#include <string>

#include "Definitions.hpp"
#include "HttpRequest.hpp"
#include "HttpVersion.hpp"
#include "Method.hpp"
#include "Result.hpp"

static constexpr unsigned short NumOfElementsInRequestLine = 3;

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
