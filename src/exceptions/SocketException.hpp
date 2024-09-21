#pragma once

#include <array>
#include <cstring>
#include <sstream>
#include <stdexcept>

class SocketException : public std::runtime_error
{
public:
    explicit SocketException(std::string_view message) : std::runtime_error(buildErrorMessage(message)) {}

    explicit SocketException(std::string_view message, int error_number)
        : std::runtime_error(buildErrorMessage(message, error_number))
    {
    }

private:
    static std::string buildErrorMessage(std::string_view message)
    {
        std::stringstream final_message;
        final_message << "Socket Error: " << message;
        return final_message.str();
    }

    static std::string buildErrorMessage(std::string_view message, int error_number)
    {
        static constexpr size_t      BufferSize = 256;
        std::array<char, BufferSize> buffer{};

        // GNU version of strerror_r returns char*
        char* error_message = strerror_r(error_number, buffer.data(), buffer.size());

        std::stringstream final_message;
        final_message << "Socket Error: " << message << ": " << error_message;

        return final_message.str();
    }
};
