#include "Classes.h"
#include <iostream>

int main()
{
    Server server;

    std::cout << "Server waiting for connection..." << std::endl;

    server.isConnected();

    std::cout << "Client connected!" << std::endl;

    server.playGame(menu(server));
}
