#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

class SocketException : public std::runtime_error
{
public:
    explicit SocketException(std::string_view message) : std::runtime_error(message.data()) {}

    explicit SocketException(std::string_view message, int error_number)
        : std::runtime_error(buildErrorMessage(message, error_number))
    {
    }

private:
    static std::string buildErrorMessage(std::string_view message, int error_number)
    {
        const std::string error_message = std::system_category().message(error_number);

        std::stringstream final_message;
        final_message << message << ": " << error_message;

        return final_message.str();
    }
};
