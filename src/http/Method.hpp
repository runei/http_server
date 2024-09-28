#pragma once

#include <array>
#include <string>

#include "HttpStatusCode.hpp"
#include "Result.hpp"

enum class Method
{
    NotSupported,
    Get
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
    static constexpr std::array<std::pair<std::string_view, Method>, 1> StringToMethodArray = {{{"GET", Method::Get}}};
};
