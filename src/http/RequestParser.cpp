#include "RequestParser.hpp"

#include <sstream>

RequestParserResult RequestParser::parse(const std::string& raw_request)
{
    HttpRequest http_request;

    RequestLine request_line = extractRequestLine(raw_request);

    auto method = extractMethod(request_line);
    if (method == Method::NotSupported)
    {
        return RequestParserResult(HttpStatusCode::MethodNotAllowed);
    }

    auto url = extractUrl(request_line);

    auto http_version = extractHttpVersion(request_line);
    if (http_version == HttpVersion::NotSupported)
    {
        return RequestParserResult(HttpStatusCode::HttpVersionNotSupported);
    }

    auto headers = extractHeaders(raw_request);
    if (headers.empty())
    {
        return RequestParserResult(HttpStatusCode::BadRequest);
    }

    http_request =
        HttpRequest::Builder().setMethod(method).setUrl(url).setHttpVersion(http_version).setHeaders(headers).build();

    return RequestParserResult(http_request);
}

RequestLine RequestParser::extractRequestLine(const std::string& raw_request)
{
    RequestLine request_line;

    std::istringstream input_string{raw_request, std::ios_base::in};
    std::string        word;

    size_t idx = 0;
    while (idx < request_line.size() && input_string >> word)
    {
        request_line[idx] = word;
        ++idx;
    }

    return request_line;
}

Method RequestParser::extractMethod(const RequestLine& request_line)
{
    return MethodHelper::getMethod(request_line[0]);
}

std::string RequestParser::extractUrl(const RequestLine& request_line)
{
    return request_line[1];
}

HttpVersion RequestParser::extractHttpVersion(const RequestLine& request_line)
{
    return HttpVersionHelper::getHttpVersion(request_line[2]);
}

HttpHeaders RequestParser::extractHeaders(const std::string& raw_request)
{
    HttpHeaders headers;

    size_t headers_start = raw_request.find("\r\n");
    if (headers_start == std::string::npos)
    {
        return headers;
    }

    headers_start += 2;
    std::string        raw_request_substr = raw_request.substr(headers_start);
    std::istringstream request_stream{raw_request_substr, std::ios_base::in};
    std::string        line;

    while (std::getline(request_stream, line) && line != "\r")
    {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos)
        {
            auto key   = trim(line.substr(0, colon_pos));
            auto value = trim(line.substr(colon_pos + 1));
            headers.emplace(key, value);
        }
    }
    return headers;
}

std::string RequestParser::trim(const std::string& str)
{
    std::size_t first = str.find_first_not_of(" \t\r\n");

    if (first == std::string_view::npos)
    {
        return {};
    }

    std::size_t last = str.find_last_not_of(" \t\r\n");

    return str.substr(first, last - first + 1);
}
