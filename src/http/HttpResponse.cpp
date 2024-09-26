#include "HttpResponse.hpp"

#include <sstream>

#include "Definitions.hpp"

HttpResponse::HttpResponse(HttpStatusCode                                         status_code,
                           std::unordered_map<std::string_view, std::string_view> headers,
                           std::string_view                                       body)
    : m_status_code(status_code), m_headers(std::move(headers)), m_body(body)
{
}

std::string HttpResponse::buildResponse() const
{
    std::ostringstream response;

    auto status_message = HttpStatusCodeHelper::getHttpStatusDescription(m_status_code);

    response << HttpVersion << " " << status_message << std::endl;

    for (const auto& header : m_headers)
    {
        response << header.first << ": " << header.second << std::endl;
    }

    response << std::endl;

    response << m_body;

    return response.str();
}

HttpResponse::Builder& HttpResponse::Builder::setStatusCode(HttpStatusCode status_code)
{
    m_status_code = status_code;
    return *this;
}

HttpResponse::Builder& HttpResponse::Builder::addHeader(std::string_view key, std::string_view value)
{
    m_headers[key] = value;
    return *this;
}

HttpResponse::Builder& HttpResponse::Builder::setBody(std::string_view body)
{
    m_body = body;
    return *this;
}

HttpResponse HttpResponse::Builder::build() const
{
    return {m_status_code, m_headers, m_body};
}
