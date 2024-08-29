/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:13:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/29 14:31:16 by mel-kouc         ###   ########.fr       */
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
#include <vector>
#include "../include/reply.hpp"

#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>


class Bot
{
	private :
		int port;
		std::string server_ip;
		int bot_fd;
		std::string password;
		struct sockaddr_in server_addr;
		bool terminate;
		void Cleanup();
		std::map<std::string, bool> client_in_game;
		std::map<std::string, std::string> current_game; // Tracks the current game of each client
	public :
		static void signalHandler(int signal);
		Bot(const std::string &ip, int port, const std::string &password);
		void	Run();
		void	ConnectToServer();
		bool	Authenticate();
		void	PlayGame();
		std::string ReceiveMessage();
		int		ChoiceToInt(const std::string &choice);
		void	SendMessage(const std::string &message);
		void	PrSendMessage(const std::string &message, const std::string &client_nick);
		void	PlayNwetat(const std::string &sender);
    	// void	PlayRoshambo(const std::string &sender);
    	void	PlayRoshambo(const std::string &sender, const std::string &content);
		
		~Bot();
};

#endif

// privmsg bot paper
// privmsg bot paper
// :bot!~ahmed@e3r9p11.1337.ma PRIVMSG ew :Bot chose paper
// :bot!~ahmed@e3r9p11.1337.ma PRIVMSG ew :It's a tie!
// :bot!~ahmed@e3r9p11.1337.ma PRIVMSG ew :Send 'rock', 'paper', or 'scissors' to play again, or 'exit' to quit.