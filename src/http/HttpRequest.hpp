#pragma once

#include <optional>
#include <string>

#include "Definitions.hpp"
#include "Method.hpp"

class HttpRequest
{
public:
    class Builder;

    [[nodiscard]] Method                          getMethod() const;
    [[nodiscard]] std::string_view                getUrl() const;
    [[nodiscard]] std::optional<std::string_view> getHeader(std::string_view key) const;
    [[nodiscard]] HttpHeaders                     getHeaders() const;

private:
    HttpRequest(const Method& method, std::string_view url, HttpHeaders headers);

    Method           m_method;
    std::string_view m_url;
    HttpHeaders      m_headers;
};

class HttpRequest::Builder
{
public:
    Builder() = default;
    Builder&    setMethod(std::string_view method);
    Builder&    setUrl(std::string_view url);
    Builder&    addHeader(std::string_view key, std::string_view value);
    HttpRequest build();

private:
    Method           m_method{Method::NotSupported};
    std::string_view m_url;
    HttpHeaders      m_headers;
};
