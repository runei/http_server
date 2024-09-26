#include "HttpRequest.hpp"

#include "SocketException.hpp"

HttpRequest::HttpRequest(const Method&                                          method,
                         const Url&                                             url,
                         std::unordered_map<std::string_view, std::string_view> headers)
    : m_method(method.value()), m_url(url.value()), m_headers(std::move(headers))
{
    if (m_method.empty() || m_url.empty())
    {
        throw SocketException("HttpRequest: Method and URL must not be empty.");
    }
}

std::string_view HttpRequest::getMethod() const
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

std::unordered_map<std::string_view, std::string_view> HttpRequest::getHeaders() const
{
    return m_headers;
}

HttpRequest::Builder& HttpRequest::Builder::setMethod(std::string_view method)
{
    m_method = method;
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
    return {Method(m_method), Url(m_url), m_headers};
}
