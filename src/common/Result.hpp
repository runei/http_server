#pragma once

#include <variant>

#include "HttpStatusCode.hpp"
#include "SocketException.hpp"

template <typename T>
    requires(!std::is_void_v<T>)
class Result
{
public:
    explicit Result(T value) : m_variant(value) {};

    explicit Result(HttpStatusCode error) : m_variant(error) {};

    [[nodiscard]] bool ok() const { return std::holds_alternative<T>(m_variant); }

    T getResult() const
    {
        if (!ok())
        {
            throw SocketException("Result: Attempted to access result on an error state");
        }
        return std::get<T>(m_variant);
    }

    [[nodiscard]] HttpStatusCode getError() const
    {
        if (ok())
        {
            throw SocketException("Result: Attempted to access error on a success state");
        }
        return std::get<HttpStatusCode>(m_variant);
    }

private:
    std::variant<T, HttpStatusCode> m_variant;
};
