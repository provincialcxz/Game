#include "Classes.h"
#include <iostream>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

Server::Server() {}

bool Server::isConnected()
{
	const int MAXSTRLEN = 255;
	WSADATA wsaData;
	sockaddr_in addr;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip_addr_.c_str(), &addr.sin_addr);
	addr.sin_port = htons(8181);

	bind(socket_, (SOCKADDR*)&addr, sizeof(addr));
	listen(socket_, 1);
	socketClient_ = accept(socket_, NULL, NULL);

	if (socketClient_ <= -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Server::~Server()
{
	closesocket(socketClient_);
	closesocket(socket_);
	WSACleanup();
}

void Server::send_message(const std::string& message)
{
	send(socketClient_, message.c_str(), message.size(), 0);
}

std::string Server::recive_message()
{
	char buf[200];
	int i = recv(socketClient_, buf, 200, 0);

	return buf;
}

void Server::playRound(int roundNumber, int roundsToPlay)
{
	std::cout << "Round " << roundNumber << " (Server)" << std::endl;

	int serverChoice = generateChoice();
	send_message(std::to_string(serverChoice));

	int clientChoice = std::stoi(recive_message());
	determineWinner(serverChoice, clientChoice);
}

void Server::playGame(int roundsToPlay)
{
	for (int round = 1; round <= roundsToPlay; ++round)
	{
		playRound(round, roundsToPlay);
	}
	std::cout << "Game over!" << std::endl;
}

int Server::generateChoice()
{
	int answer;
	std::cout << "Enter your turn: (1 - Rock, 2 - Paper, 3 - Scissors)";
	std::cin >> answer;

	return answer;
}

void Server::determineWinner(int serverChoice, int clientChoice)
{
	if (serverChoice == clientChoice)
	{
		std::cout << "It's a tie!" << std::endl;
	}
	else if ((serverChoice == 1 && clientChoice == 3) || (serverChoice == 2 && clientChoice == 1) || (serverChoice == 3 && clientChoice == 2))
	{
		std::cout << "You wins!" << std::endl;
	}
	else
	{
		std::cout << "You lose!" << std::endl;
	}
}

Client::Client()
{
	const int MAXSTRLEN = 255;
	WSADATA wsaData;
	sockaddr_in addr;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip_addr_.c_str(), &addr.sin_addr);
	addr.sin_port = htons(8181);
	connect(socket_, (SOCKADDR*)&addr, sizeof(addr));
}

Client::~Client()
{
	closesocket(socket_);
	WSACleanup();
}

void Client::send_message(const std::string& message)
{
	send(socket_, message.c_str(), message.size(), 0);
}

std::string Client::recive_message()
{
	char buf[200];
	int i = recv(socket_, buf, 200, 0);

	return buf;
}

void Client::playRound(int roundNumber, int roundsToPlay)
{
	std::cout << "Round " << roundNumber << " (Client)" << std::endl;

	int clientChoice = std::stoi(recive_message());
	int serverChoice = generateChoice();

	send_message(std::to_string(serverChoice));
	determineWinner(serverChoice, clientChoice);
}

void Client::playGame(int roundsToPlay)
{
	for (int round = 1; round <= roundsToPlay; ++round)
	{
		playRound(round, roundsToPlay);
	}
	system("cls");
	std::cout << "Game over!" << std::endl;
	system("pause");
}

int Client::generateChoice()
{
	int answer;
	std::cout << "Enter your turn: (1 - Rock, 2 - Paper, 3 - Scissors)";
	std::cin >> answer;

	return answer;
}

void Client::determineWinner(int serverChoice, int clientChoice)
{
	if (serverChoice == clientChoice)
	{
		std::cout << "It's a tie!" << std::endl;
	}
	else if ((clientChoice == 1 && serverChoice == 3) || (clientChoice == 2 && serverChoice == 1) || (clientChoice == 3 && serverChoice == 2))
	{
		std::cout << "Client wins!" << std::endl;
	}
	else
	{
		std::cout << "Server wins!" << std::endl;
	}
}

int menu(Server server)
{
	std::cout << "\tWelcome to my game!!!\n How many times do you want to play the game?\n";

	int roundsToPlay;
	std::cin >> roundsToPlay;

	std::cout << "\n\tLet's go\n";

	server.send_message(std::to_string(roundsToPlay));

	return roundsToPlay;
}