#pragma once

#include <string>
#include <unordered_map>

#include "Definitions.hpp"
#include "HttpStatusCode.hpp"
#include "HttpVersion.hpp"

class HttpResponse
{
public:
    class Builder;

    [[nodiscard]] std::string buildResponse() const;

private:
    HttpVersion    m_http_version;
    HttpStatusCode m_status_code;
    HttpHeaders    m_headers;
    std::string    m_body;

    HttpResponse(HttpVersion http_version, HttpStatusCode status_code, HttpHeaders headers, std::string body);
};

class HttpResponse::Builder
{
public:
    Builder&     setHttpVersion(HttpVersion http_version);
    Builder&     setStatusCode(HttpStatusCode status_code);
    Builder&     addHeader(const std::string& key, const std::string& value);
    Builder&     setBody(std::string body);
    HttpResponse build() const;

private:
    HttpVersion    m_http_version{HttpVersion::NotSupported};
    HttpStatusCode m_status_code{HttpStatusCode::OK};
    HttpHeaders    m_headers;
    std::string    m_body;
};
