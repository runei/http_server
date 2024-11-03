#include "Client.hpp"

#include <sys/socket.h>
#include <sys/types.h>

#include <array>
#include <bit>
#include <cerrno>
#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Definitions.hpp"

Client::~Client()
{
    closeSocket();
}

bool Client::connectToServer(const std::string& ip_address, int port)
{
    m_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock_fd < 0)
    {
        std::cerr << "Client: Error: Could not create socket\n";
        return false;
    }

    return connectSocket(ip_address, port);
}

bool Client::sendRequest(const std::string& request) const
{
    if (m_sock_fd < 0)
    {
        std::cerr << "Client: Error: No connection established\n";
        return false;
    }

    const ssize_t bytes_sent = send(m_sock_fd, request.data(), request.size(), 0);
    if (bytes_sent < 0)
    {
        std::cerr << "Client: Error: Failed to send request\n";
        return false;
    }

    return true;
}

std::string Client::getResponse() const
{
    if (m_sock_fd < 0)
    {
        std::cerr << "Client: Error: No connection established\n";
        return "";
    }

    std::array<char, BufferSize> buffer{};
    std::string                  response;

    while (true)
    {
        const ssize_t received_bytes = recv(m_sock_fd, buffer.data(), buffer.size(), 0);
        if (received_bytes > 0)
        {
            response.append(buffer.data(), received_bytes);
        }
        else if (received_bytes == 0)
        {
            break;
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            usleep(PollIntervalMicroseconds);
        }
        else
        {
            std::cerr << "Client: Error receiving response\n";
            break;
        }
    }

    return response;
}

bool Client::connectSocket(const std::string& ip_address, int port)
{
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(port);

    if (inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr) <= 0)
    {
        std::cerr << "Client: Error: Invalid IP address\n";
        closeSocket();
        return false;
    }

    if (connect(m_sock_fd, std::bit_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0)
    {
        if (errno != EINPROGRESS)
        {
            std::cerr << "Client: Error: Connection to server failed\n";
            closeSocket();
            return false;
        }
    }

    std::cout << "Connected to server at " << ip_address << ":" << port << "\n";
    return true;
}

void Client::closeSocket()
{
    if (m_sock_fd >= 0)
    {
        close(m_sock_fd);
        m_sock_fd = -1;
    }
}
