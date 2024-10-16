#include "HttpRequest.hpp"

#include "SocketException.hpp"

HttpRequest::HttpRequest() : m_method(Method::NotSupported), m_http_version(HttpVersion::NotSupported) {}

HttpRequest::HttpRequest(const Method& method, std::string url, HttpVersion http_version, HttpHeaders headers)
    : m_method(method), m_url(std::move(url)), m_http_version(http_version), m_headers(std::move(headers))
{
}

Method HttpRequest::getMethod() const
{
    return m_method;
}

std::string HttpRequest::getUrl() const
{
    return m_url;
}

HttpVersion HttpRequest::getHttpVersion() const
{
    return m_http_version;
}

std::optional<std::string_view> HttpRequest::getHeader(const std::string& key) const
{
    auto header = m_headers.find(key);
    if (header != m_headers.end())
    {
        return header->second;
    }
    return std::nullopt;
}

HttpRequest::Builder& HttpRequest::Builder::setMethod(Method method)
{
    m_method = method;
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::setUrl(std::string url)
{
    m_url = std::move(url);
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::setHttpVersion(HttpVersion http_version)
{
    m_http_version = http_version;
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::setHeaders(HttpHeaders headers)
{
    m_headers = std::move(headers);

    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::addHeader(const std::string& key, const std::string& value)
{
    m_headers.emplace(key, value);
    return *this;
}

HttpRequest HttpRequest::Builder::build()
{
    return {m_method, m_url, m_http_version, m_headers};
}
