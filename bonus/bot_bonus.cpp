/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/20 11:36:54 by mel-kouc         ###   ########.fr       */
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
	// server_addr.sin_addr.s_addr = inet_addr(address.c_str());
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

	size_t bytes_received = recv(bot_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received < 0)
		throw std::runtime_error("Failed to receive message");
	buffer[bytes_received] = '\0';
	// std::cout << "Received message: " << buffer << std::endl;
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
        std::cerr << "Failed to send message " << std::endl;
    }
}

// add
void Bot::PrSendMessage(const std::string &message, const std::string &client_nick)
{
    std::string formatted_message = "PRIVMSG " + client_nick + " :" + message + "\r\n";
    if (send(bot_fd, formatted_message.c_str(), formatted_message.length(), 0) < 0)
    {
        // RemoveClient(client_nick); // Remove client if sending fails
        std::cerr << "Failed to send message to client " << client_nick << std::endl;
    }
}


// void Bot::RemoveClient(int client_fd) {
//     close(client_fd);
//     connected_clients.erase(client_fd);
//     std::cout << "Client " << client_fd << " disconnected and removed from the list." << std::endl;
// }


// void Bot::RemoveClient(int client_fd)
// {
//     close(client_fd);
//     client_fds.erase(std::remove(client_fds.begin(), client_fds.end(), client_fd), client_fds.end());
// }


void	Bot::PlayGame()
{
	std::srand(std::time(0));
	std::string choices[] = {"rock", "paper", "scissors"};
	while (true)
    {
        std::string client_message = ReceiveMessage();
        if (client_message.size() >= 2 && client_message.substr(client_message.size() - 2) == "\r\n") 
            client_message.erase(client_message.size() - 2);
        
        std::istringstream iss(client_message);
    
        // Variables to hold the parts of the message
        std::string senderdomaine;
        std::string command;
        std::string receiver;
        std::string msgContent;
        
        iss >> senderdomaine;
        std::string sender = senderdomaine.substr(1, senderdomaine.find('!') - 1);
        iss >> command;
        iss >> receiver;
        std::getline(iss, msgContent); // Get the rest of the line


        // Remove the leading ': ' from the message content
        if (!msgContent.empty() && msgContent[0] == ' ' && msgContent[1] == ':') {
            msgContent = msgContent.substr(2);
        }

        std::cout << "msgContent =>>" << msgContent<< "<<=" <<std::endl;
            // Check if the command is 'privmsg'
            if (command == "PRIVMSG")
            {
                if (msgContent == "start")
                {
                    PrSendMessage("Game started. Send 'rock', 'paper', or 'scissors'.", sender);
                }
                else if (msgContent == "exit")
                {
                    PrSendMessage("Game ended.", sender);
                    break;
                }
                else
                {
                    int client_choice = ChoiceToInt(msgContent);
                    if (client_choice != -1)
                    {
                        int bot_choice = std::rand() % 3;
                        PrSendMessage("Bot chose " + std::string(choices[bot_choice]), sender);
                        
                        switch (client_choice)
                        {
                        case 0: // client chose rock
                            switch (bot_choice)
                            {
                            case 0: PrSendMessage("It's a tie", sender); break;
                            case 1: PrSendMessage("Bot wins!", sender); break;
                            case 2: PrSendMessage("You win!", sender); break;
                            }
                            break;
                        case 1: // Client chose paper
                            switch (bot_choice)
                            {
                            case 0: PrSendMessage("You win!", sender); break;
                            case 1: PrSendMessage("It's a tie!", sender); break;
                            case 2: PrSendMessage("Bot wins!", sender); break;
                            }
                            break;
                        case 2: // Client chose scissors
                            switch (bot_choice)
                            {
                            case 0: PrSendMessage("Bot wins!", sender); break;
                            case 1: PrSendMessage("You win!", sender); break;
                            case 2: PrSendMessage("It's a tie!", sender); break;
                            }
                            break;
                        }
                    }
                    else
                    {
                        PrSendMessage("Invalid input. Send 'rock', 'paper', or 'scissors' to play, or 'exit' to quit.", sender);
                    }
                }
            }
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