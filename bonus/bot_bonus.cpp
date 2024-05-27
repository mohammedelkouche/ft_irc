/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/27 17:11:46 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bot_bonus.hpp"
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

void	Bot::connect_to_server()
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

std::string	Bot::receive_message()
{
	char buffer[1024];

	int bytes_received = recv(bot_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received < 0)
		throw std::runtime_error("Failed to receive message");
	buffer[bytes_received] = '\0';
	return (std::string (buffer));
}

int	Bot::choice_to_int(const std::string &choice)
{
	if (choice == "rock")
		return (0);
	if (choice == "paper")
		return (1);
	if (choice == "scissors")
		return (2);
	return (-1);
}

void Bot::send_message(const std::string &message) {
    if (send(bot_fd, message.c_str(), message.length(), 0) < 0) {
        throw std::runtime_error("Failed to send message");
    }
}

void	Bot::play_game()
{
	std::srand(std::time(0));
	std::string choices[] = {"rock", "paper", "scissors"};
	while(true)
	{
		std::string client_message = receive_message();
		int client_choice = choice_to_int(client_message);
		if (client_message == "start")
			send_message("Game started. Send 'rock', 'paper', or 'scissors'.");
		else if (client_choice != -1)
		{
			int bot_choice = std::rand() % 3;
			send_message("Bot chose " + std::string(choices[bot_choice]));
			
			switch(client_choice)
			{
				case 0 : // client chose rock
					switch (bot_choice)
					{
						case 0 : send_message("It's a tie"); break;
						case 1 : send_message("Bot wins! Paper covers rock."); break;
                        case 2 : send_message("You win! Rock crushes scissors."); break;
                    }
					break;
				case 1 : // Client chose paper
				 	switch (bot_choice) 
					{
                        case 0: send_message("You win! Paper covers rock."); break;
                        case 1: send_message("It's a tie!"); break;
                        case 2: send_message("Bot wins! Scissors cut paper."); break;
                    }
                    break;
                case 2 : // Client chose scissors
                    switch (bot_choice) {
                        case 0: send_message("Bot wins! Rock crushes scissors."); break;
                        case 1: send_message("You win! Scissors cut paper."); break;
                        case 2: send_message("It's a tie!"); break;
                    }
                    break;
			}
		}
		else if (client_message == "exit")
		{
            send_message("Game ended.");
            break;
        }
		else 
            send_message("Invalid input. Send 'rock', 'paper', or 'scissors' to play, or 'exit' to quit.");

	}
}

void	Bot::run()
{
	connect_to_server();
	play_game();
	// while(true)
	// {
			
	// }
}

Bot::~Bot()
{}