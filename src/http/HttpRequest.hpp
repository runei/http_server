#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class HttpRequest
{
public:
    class Method;
    class Url;
    class Builder;

    [[nodiscard]] std::string_view                                       getMethod() const;
    [[nodiscard]] std::string_view                                       getUrl() const;
    [[nodiscard]] std::optional<std::string_view>                        getHeader(std::string_view key) const;
    [[nodiscard]] std::unordered_map<std::string_view, std::string_view> getHeaders() const;

private:
    HttpRequest(const Method& method, const Url& url, std::unordered_map<std::string_view, std::string_view> headers);

    std::string_view                                       m_method;
    std::string_view                                       m_url;
    std::unordered_map<std::string_view, std::string_view> m_headers;
};

class HttpRequest::Method
{
public:
    explicit Method(std::string_view method) : m_method(method) {}
    [[nodiscard]] std::string_view value() const { return m_method; }

private:
    std::string_view m_method;
};

class HttpRequest::Url
{
public:
    explicit Url(std::string_view url) : m_url(url) {}
    [[nodiscard]] std::string_view value() const { return m_url; }

private:
    std::string_view m_url;
};

class HttpRequest::Builder
{
public:
    Builder&    setMethod(std::string_view method);
    Builder&    setUrl(std::string_view url);
    Builder&    addHeader(std::string_view key, std::string_view value);
    HttpRequest build();

private:
    std::string_view                                       m_method;
    std::string_view                                       m_url;
    std::unordered_map<std::string_view, std::string_view> m_headers;
};
