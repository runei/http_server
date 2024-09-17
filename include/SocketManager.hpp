#pragma once

#include <memory>

#include <netinet/in.h>

class SocketManager
{
public:
    // Deleted copy constructor and assignment operator to ensure singleton
    SocketManager(const SocketManager&)            = delete;
    SocketManager& operator=(const SocketManager&) = delete;

    static SocketManager& getInstance();
    void                  createSocket();
    void                  bindSocket(uint16_t port);
    void                  listenSocket(int n_connections);
    int                   acceptConnection();

private:
    SocketManager() = default;

    void setAddress(uint16_t port);

    int         m_server_fd{-1};
    sockaddr_in m_address{};
};
