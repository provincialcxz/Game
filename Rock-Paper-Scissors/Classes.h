#pragma once
#include <string>
#include "WinSock2.h"

class Server
{
    unsigned int socket_;
    unsigned int socketClient_;
    std::string ip_addr_ = "127.0.0.1";

public:
    Server();
    ~Server();

    void playRound(int roundNumber, int roundsToPlay);
    void playGame(int roundsToPlay);
    int generateChoice();
    void determineWinner(int serverChoice, int clientChoice);

    bool isConnected();
    void send_message(const std::string& message);
    std::string recive_message();
};

class Client
{
    unsigned int socket_;
    std::string ip_addr_ = "127.0.0.1";

public:
    Client();
    ~Client();

    void playRound(int roundNumber, int roundsToPlay);
    void playGame(int roundsToPlay);
    int generateChoice();
    void determineWinner(int serverChoice, int clientChoice);

    void send_message(const std::string& message);
    std::string recive_message();
};

int menu(Server server);