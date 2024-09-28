#include "HttpRequest.hpp"

#include "SocketException.hpp"

HttpRequest::HttpRequest(const Method& method, std::string_view url, HttpHeaders headers)
    : m_method(method), m_url(url), m_headers(std::move(headers))
{
}

Method HttpRequest::getMethod() const
{
    return m_method;
}

std::string_view HttpRequest::getUrl() const
{
    return m_url;
}

std::optional<std::string_view> HttpRequest::getHeader(std::string_view key) const
{
    auto header = m_headers.find(key);
    if (header != m_headers.end())
    {
        return header->second;
    }
    return std::nullopt;
}

HttpHeaders HttpRequest::getHeaders() const
{
    return m_headers;
}

HttpRequest::Builder& HttpRequest::Builder::setMethod(std::string_view method)
{
    m_method = MethodHelper::getMethod(method);
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::setUrl(std::string_view url)
{
    m_url = url;
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::addHeader(std::string_view key, std::string_view value)
{
    m_headers.emplace(key, value);
    return *this;
}

HttpRequest HttpRequest::Builder::build()
{
    return {m_method, m_url, m_headers};
}
