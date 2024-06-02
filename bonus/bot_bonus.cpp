/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/06/02 17:03:41 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot_bonus.hpp"
#include<cstring>
#include<string>


Bot::Bot(const std::string  ip, int port) : port(port), server_ip(ip), bot_fd(-1)
{
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0)
		throw std::runtime_error("Invalid address/ Address not supported");

}

void	Bot::ConnectToServer()
{
	bot_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (bot_fd < 0)
		throw std::runtime_error("Socket creation error");
	// if (connect(bot_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) < 0))
	if (connect(bot_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		close(bot_fd);
		// throw std::runtime_error("Connection Failed");
		throw std::runtime_error("Connection failed: " + std::string(strerror(errno)));

	}
	// std::cout << "Connected to the server" << std::endl;
	std::cout << "Connected to server on port " << port << std::endl; // Use the port field here

}

std::string	Bot::ReceiveMessage()
{
	char buffer[1024];

	int bytes_received = recv(bot_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received < 0)
		throw std::runtime_error("Failed to receive message");
	buffer[bytes_received] = '\0';
	return (std::string (buffer));
}

int	Bot::ChoiceToInt(const std::string &choice)
{
	if (choice == "rock")
		return (0);
	if (choice == "paper")
		return (1);
	if (choice == "scissors")
		return (2);
	return (-1);
}

void Bot::SendMessage(const std::string &message) {
    if (send(bot_fd, message.c_str(), message.length(), 0) < 0) {
        throw std::runtime_error("Failed to send message");
    }
}

void	Bot::PlayGame()
{
	std::srand(std::time(0));
	std::string choices[] = {"rock", "paper", "scissors"};
	while(true)
	{
		std::string client_message = ReceiveMessage();
		int client_choice = ChoiceToInt(client_message);
		if (client_message == "start")
			SendMessage("Game started. Send 'rock', 'paper', or 'scissors'.");
		else if (client_choice != -1)
		{
			int bot_choice = std::rand() % 3;
			SendMessage("Bot chose " + std::string(choices[bot_choice]));
			
			switch(client_choice)
			{
				case 0 : // client chose rock
					switch (bot_choice)
					{
						case 0 : SendMessage("It's a tie"); break;
						case 1 : SendMessage("Bot wins! Paper covers rock."); break;
                        case 2 : SendMessage("You win! Rock crushes scissors."); break;
                    }
					break;
				case 1 : // Client chose paper
				 	switch (bot_choice) 
					{
                        case 0: SendMessage("You win! Paper covers rock."); break;
                        case 1: SendMessage("It's a tie!"); break;
                        case 2: SendMessage("Bot wins! Scissors cut paper."); break;
                    }
                    break;
                case 2 : // Client chose scissors
                    switch (bot_choice) {
                        case 0: SendMessage("Bot wins! Rock crushes scissors."); break;
                        case 1: SendMessage("You win! Scissors cut paper."); break;
                        case 2: SendMessage("It's a tie!"); break;
                    }
                    break;
			}
		}
		else if (client_message == "exit")
		{
            SendMessage("Game ended.");
            break;
        }
		else 
            SendMessage("Invalid input. Send 'rock', 'paper', or 'scissors' to play, or 'exit' to quit.");

	}
}

bool	Bot::Authenticate()
{
	std::string nick, user, pass;
    std::cout << "Enter password: ";
    std::cin >> pass;
    std::cout << "Enter nickname: ";
    std::cin >> nick;
    std::cout << "Enter username: ";
    std::cin >> user;

    SendMessage("PASS " + pass + "\r\n");
    SendMessage("NICK " + nick + "\r\n");
    SendMessage("USER " + user + " 0 * " + user + "\r\n");

    std::string response = ReceiveMessage();
    std::cout << "Server: " << response << std::endl;

    // Assuming "001" is the successful login code
    if (response.find("001") != std::string::npos)
	{
        std::cout << "Authentication successful." << std::endl;
        return true;
    }
	else
        return false;
}

void	Bot::Run()
{
	ConnectToServer();
	while (!Authenticate()) {
		std::cout << "Authentication failed. Please try again." << std::endl;
    }
	PlayGame();
}

Bot::~Bot()
{}