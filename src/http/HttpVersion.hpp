#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <utility>

enum class HttpVersion : std::uint8_t
{
    NotSupported,
    Http11
};

class HttpVersionHelper
{
public:
    [[nodiscard]] static HttpVersion getHttpVersion(std::string_view input)
    {
        for (const auto& [string_http_version, http_version] : StringToHttpVersionArray)
        {
            if (input == string_http_version)
            {
                return http_version;
            }
        }
        return HttpVersion::NotSupported;
    }

    [[nodiscard]] static std::string_view toString(HttpVersion version)
    {
        for (const auto& [string_http_version, http_version] : StringToHttpVersionArray)
        {
            if (version == http_version)
            {
                return string_http_version;
            }
        }
        return "Not Supported";
    }

private:
    static constexpr std::array<std::pair<std::string_view, HttpVersion>, 1> StringToHttpVersionArray = {
        std::make_pair("HTTP/1.1", HttpVersion::Http11),
    };
};
