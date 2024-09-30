#include <sys/socket.h>

#include <array>
#include <iostream>

#include <netinet/in.h>
#include <unistd.h>

#include "HttpResponse.hpp"
#include "HttpStatusCode.hpp"
#include "SocketManager.hpp"

constexpr int PORT = 8080;

std::string buildHttpResponse(const std::string& content)
{
    auto response = HttpResponse::Builder()
                        .setStatusCode(HttpStatusCode::OK)
                        .addHeader("Content-Lenght", std::to_string(content.size()))
                        .addHeader("Content-Type", "text/html")
                        .addHeader("Connection", "close")
                        .setBody(content)
                        .build();

    return response.buildResponse();
}

void handleClient(int client_socket)
{
    static constexpr size_t      BufferSize = 30000;
    std::array<char, BufferSize> buffer     = {0};

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
    static constexpr size_t MaxNumOfSockets = 10;
    try
    {
        std::cout << "Running" << std::endl;

        auto& socket_manager = SocketManager::getInstance();

        socket_manager.createSocket(PORT);

        socket_manager.listenSocket(MaxNumOfSockets);

        std::cout << "Listening on port " << PORT << std::endl;

        while (true)
        {
            auto client_socket = socket_manager.acceptConnection();
            if (!client_socket)
            {
                std::cerr << "Accepting connection failed" << std::endl;
                continue;
            }

            handleClient(client_socket.value());
            close(client_socket.value());
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
