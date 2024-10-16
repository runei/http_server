#pragma once

#include <optional>
#include <string>

#include "Definitions.hpp"
#include "HttpVersion.hpp"
#include "Method.hpp"

class HttpRequest
{
public:
    class Builder;

    HttpRequest();

    [[nodiscard]] Method                          getMethod() const;
    [[nodiscard]] std::string                     getUrl() const;
    [[nodiscard]] HttpVersion                     getHttpVersion() const;
    [[nodiscard]] std::optional<std::string_view> getHeader(const std::string& key) const;

private:
    HttpRequest(const Method& method, std::string url, HttpVersion http_version, HttpHeaders headers);

    Method      m_method;
    std::string m_url;
    HttpVersion m_http_version;
    HttpHeaders m_headers;
};

class HttpRequest::Builder
{
public:
    Builder() = default;
    Builder&    setMethod(Method method);
    Builder&    setUrl(std::string url);
    Builder&    setHttpVersion(HttpVersion http_version);
    Builder&    setHeaders(HttpHeaders headers);
    Builder&    addHeader(const std::string& key, const std::string& value);
    HttpRequest build();

private:
    Method      m_method{Method::NotSupported};
    std::string m_url;
    HttpVersion m_http_version{HttpVersion::NotSupported};
    HttpHeaders m_headers;
};
