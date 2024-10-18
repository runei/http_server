#include "Server.hpp"

constexpr int Port = 8080;

int main()
{
    Server server(Port);

    server.start();

    return 0;
}
