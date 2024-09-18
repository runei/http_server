#include <sys/socket.h>

#include <array>
#include <iostream>

#include <netinet/in.h>
#include <unistd.h>

#include "SocketManager.hpp"

constexpr int PORT = 8080;

std::string buildHttpResponse(const std::string& content)
{
    std::string response = "HTTP/1.1 200 OK\n";
    response += "Content-Lenght: " + std::to_string(content.size()) + "\n";
    response += "Content-Type: text/html\n";
    response += "Connection: close\n\n";
    response += content;
    return response;
}

void handleClient(int client_socket)
{
    std::array<char, 30000> buffer = {0};

    ssize_t bytes_read = read(client_socket, buffer.data(), buffer.size());

    if (bytes_read > 0)
    {
        std::cout << "Received request:\n" << std::string(buffer.data(), bytes_read) << std::endl;

        std::string content  = "<html><body><h1>Hello from C++20 HTTP Server!</h1></body></html>";
        std::string response = buildHttpResponse(content);

        send(client_socket, response.c_str(), response.size(), 0);
        std::cout << "HTTP reponse sent\n";
    }

    close(client_socket);
}

int main()
{
    try
    {
        std::cout << "Running" << std::endl;

        auto& socket_manager = SocketManager::getInstance();

        socket_manager.createSocket(PORT);

        socket_manager.listenSocket(10);

        std::cout << "Listening on port " << PORT << std::endl;

        while (true)
        {
            int client_socket = socket_manager.acceptConnection();
            if (client_socket < 0)
            {
                std::cerr << "Accepting connection failed" << std::endl;
                continue;
            }

            handleClient(client_socket);
            close(client_socket);
        }
        socket_manager.closeSocket();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
