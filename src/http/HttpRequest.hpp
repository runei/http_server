#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class HttpRequest
{
public:
    struct HttpMethod;
    struct HttpUrl;
    class Builder;

    HttpRequest(const HttpMethod&                                      method,
                const HttpUrl&                                         url,
                std::unordered_map<std::string_view, std::string_view> headers);

    [[nodiscard]] std::string_view                                       getMethod() const;
    [[nodiscard]] std::string_view                                       getUrl() const;
    [[nodiscard]] std::optional<std::string_view>                        getHeader(std::string_view key) const;
    [[nodiscard]] std::unordered_map<std::string_view, std::string_view> getHeaders() const;

private:
    std::string_view                                       m_method;
    std::string_view                                       m_url;
    std::unordered_map<std::string_view, std::string_view> m_headers;
};

struct HttpRequest::HttpMethod
{
    std::string_view Method;
};

struct HttpRequest::HttpUrl
{
    std::string_view Url;
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
