#include <sys/socket.h>

#include <array>
#include <iostream>

#include <netinet/in.h>
#include <unistd.h>

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
    std::cout << "Running" << std::endl;

    int         server_fd;
    int         client_socket;
    sockaddr_in address{};
    socklen_t   addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd <= 0)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, addrlen) < 0)
    {
        std::cerr << "Binding failed" << std::endl;
        return -1;
    }

    if (listen(server_fd, 10) < 0)
    {
        std::cerr << "Listening failed" << std::endl;
        return -1;
    }

    std::cout << "Listening on port " << PORT << std::endl;

    while (true)
    {
        client_socket = accept(server_fd, (sockaddr*)&address, &addrlen);
        if (client_socket < 0)
        {
            std::cerr << "Accepting connection failed" << std::endl;
            continue;
        }

        handleClient(client_socket);
    }

    return 0;
}
