#include "Client.hpp"

#include <sys/socket.h>

#include <array>
#include <bit>
#include <iostream>

#include <arpa/inet.h>
#include <unistd.h>

#include "Definitions.hpp"

Client::~Client()
{
    if (m_sock_fd >= 0)
    {
        close(m_sock_fd);
    }
}

bool Client::connectToServer(const std::string& ip_address, int port)
{
    m_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock_fd < 0)
    {
        std::cerr << "Client: Error: Could not create socket\n";
        return false;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(port);

    if (inet_pton(AF_INET, ip_address.data(), &server_address.sin_addr) <= 0)
    {
        std::cerr << "Client: Error: Invalid IP address\n";
        return false;
    }

    if (connect(m_sock_fd, std::bit_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0)
    {
        std::cerr << "Client: Error: Connection to server failed\n";
        return false;
    }

    std::cout << "Connected to server at " << ip_address << ":" << port << "\n";
    return true;
}

bool Client::sendRequest(const std::string& request) const
{
    if (m_sock_fd < 0)
    {
        std::cerr << "Client: Error: No connection established\n";
        return false;
    }

    ssize_t bytes_sent = send(m_sock_fd, request.data(), request.size(), 0);
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
    ssize_t                      received_bytes = -1;

    while ((received_bytes = recv(m_sock_fd, buffer.data(), buffer.size(), 0)) > 0)
    {
        response.append(buffer.data(), received_bytes);
    }

    if (received_bytes < 0)
    {
        std::cerr << "Client: Error receiving response\n";
    }

    return response;
}
