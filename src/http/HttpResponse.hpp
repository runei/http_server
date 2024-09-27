#pragma once

#include <string>
#include <unordered_map>

#include "Definitions.hpp"
#include "HttpStatusCode.hpp"

class HttpResponse
{
public:
    class Builder;

    [[nodiscard]] std::string buildResponse() const;

private:
    HttpStatusCode   m_status_code;
    HttpHeaders      m_headers;
    std::string_view m_body;

    HttpResponse(HttpStatusCode status_code, HttpHeaders headers, std::string_view body);
};

class HttpResponse::Builder
{
public:
    Builder&     setStatusCode(HttpStatusCode status_code);
    Builder&     addHeader(std::string_view key, std::string_view value);
    Builder&     setBody(std::string_view body);
    HttpResponse build() const;

private:
    HttpStatusCode   m_status_code{HttpStatusCode::OK};
    HttpHeaders      m_headers;
    std::string_view m_body;
};
