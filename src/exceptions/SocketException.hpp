#pragma once

#include <cstring>
#include <stdexcept>

class SocketException : public std::runtime_error
{
public:
    explicit SocketException(const std::string& message) : std::runtime_error("Socket Error: " + message) {}

    explicit SocketException(const std::string& message, int error_number)
        : std::runtime_error("Socket Error: " + message + ": " + std::string(strerror(error_number)))
    {
    }
};
