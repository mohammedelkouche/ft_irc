/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:13:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/25 16:49:48 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_BONUS_HPP
#define BOT_BONUS_HPP

#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>

class Bot
{
	private :
		int port;
		std::string server_ip;
		int bot_fd;
		struct sockaddr_in server_addr;
	public :
		Bot(const std::string ip, int port);
		void	run();
		void	connect_to_server();
		~Bot();
};

#endif