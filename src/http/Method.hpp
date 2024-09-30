#pragma once

#include <array>
#include <string>

enum class Method
{
    NotSupported,
    Get,
    Post
};

class MethodHelper
{
public:
    [[nodiscard]] static Method getMethod(std::string_view string)
    {
        for (const auto& [string_method, method] : StringToMethodArray)
        {
            if (string == string_method)
            {
                return method;
            }
        }
        return Method::NotSupported;
    }

private:
    static constexpr std::array<std::pair<std::string_view, Method>, 2> StringToMethodArray = {
        {{"GET", Method::Get}, {"POST", Method::Post}}};
};
