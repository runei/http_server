#pragma once

#include <variant>

#include "HttpStatusCode.hpp"
#include "SocketException.hpp"

template <typename T>
    requires(!std::is_void_v<T>)
class Result
{
public:
    explicit Result(const T& value) : m_variant(value) {};

    explicit Result(HttpStatusCode error) : m_variant(error) {};

    [[nodiscard]] bool success() const { return std::holds_alternative<T>(m_variant); }

    [[nodiscard]] T getResult() const
    {
        if (!success())
        {
            throw SocketException("Result: Attempted to access result on an error state");
        }
        return std::get<T>(m_variant);
    }

    [[nodiscard]] HttpStatusCode getStatus() const
    {
        if (success())
        {
            return HttpStatusCode::OK;
        }
        return std::get<HttpStatusCode>(m_variant);
    }

private:
    std::variant<T, HttpStatusCode> m_variant;
};
