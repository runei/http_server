#pragma once

#include <sys/types.h>

#include <string>

class Client
{
public:
    Client() = default;
    ~Client();

    Client(const Client&)            = default;
    Client& operator=(const Client&) = default;
    Client(Client&&)                 = default;
    Client& operator=(Client&&)      = default;

    [[nodiscard]] bool        connectToServer(const std::string& ip_address, int port);
    [[nodiscard]] bool        sendRequest(const std::string& request) const;
    [[nodiscard]] std::string getResponse() const;

private:
    bool connectSocket(const std::string& ip_address, int port);
    void closeSocket();

    static constexpr useconds_t PollIntervalMicroseconds = 100;

    int m_sock_fd{-1};
};
