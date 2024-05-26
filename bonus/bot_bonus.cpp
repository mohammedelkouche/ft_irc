/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/26 18:07:21 by mel-kouc         ###   ########.fr       */
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

void	Bot::run()
{
	connect_to_server();
	// while(true)
	// {
			
	// }
}

Bot::~Bot()
{}