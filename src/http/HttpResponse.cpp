#include "HttpResponse.hpp"

#include <sstream>

HttpResponse::HttpResponse(HttpVersion http_version, HttpStatusCode status_code, HttpHeaders headers, std::string body)
    : m_http_version(http_version), m_status_code(status_code), m_headers(std::move(headers)), m_body(std::move(body))
{
}

std::string HttpResponse::buildResponse() const
{
    std::ostringstream response;

    auto status_message = HttpStatusCodeHelper::getHttpStatusDescription(m_status_code);

    response << HttpVersionHelper::toString(m_http_version) << " " << status_message << std::endl;

    for (const auto& header : m_headers)
    {
        response << header.first << ": " << header.second << std::endl;
    }

    response << std::endl;

    response << m_body;

    return response.str();
}

HttpResponse::Builder& HttpResponse::Builder::setHttpVersion(HttpVersion http_version)
{
    m_http_version = http_version;
    return *this;
}

HttpResponse::Builder& HttpResponse::Builder::setStatusCode(HttpStatusCode status_code)
{
    m_status_code = status_code;
    return *this;
}

HttpResponse::Builder& HttpResponse::Builder::addHeader(const std::string& key, const std::string& value)
{
    m_headers.emplace(key, value);
    return *this;
}

HttpResponse::Builder& HttpResponse::Builder::setBody(std::string body)
{
    m_body = std::move(body);
    return *this;
}

HttpResponse HttpResponse::Builder::build() const
{
    return {m_http_version, m_status_code, m_headers, m_body};
}
