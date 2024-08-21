/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:13:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/21 21:45:25 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_BONUS_HPP
#define BOT_BONUS_HPP

#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>

#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>


class Bot
{
	private :
		int port;
		std::string server_ip;
		int bot_fd;
		struct sockaddr_in server_addr;
		bool terminate;
		void Cleanup();
		static void signalHandler(int signal);
		std::map<std::string, bool> client_in_game;
		// add
		// std::vector<int> client_fds;
	public :
		Bot(const std::string ip, int port);
		void	Run();
		void	ConnectToServer();
		bool	Authenticate();
		void	PlayGame();
		std::string ReceiveMessage();
		int		ChoiceToInt(const std::string &choice);
		void	SendMessage(const std::string &message);
		void	PrSendMessage(const std::string &message, const std::string &client_nick);
		void	setNonBlocking(int fd);
		// add
		// void RemoveClient(int client_fd);
		~Bot();
};

#endif