#include "Classes.h"
#include <iostream>

int main()
{
    Client client;

    int roundsToPlay;
    roundsToPlay = stoi(client.recive_message());

    std::cout << roundsToPlay << std::endl;

    client.playGame(roundsToPlay);

    return 0;
}