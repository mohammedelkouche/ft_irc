/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/06 13:20:10 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include <poll.h>
#include "./client.hpp"
#include <map>

#define BUFFER_SIZE 1024

class Server
{
	private :
		int port;
		std::string pass;
		int fd_srv_socket;
		std::vector<Client> clients;
		// std::map<int, Client>clients;
		std::vector <struct pollfd> pollfds;
		char buffer[BUFFER_SIZE];
	public :
		Server();
		Server(const Server &obj);
		Server& operator = (const Server &obj);
		void	initializeServer(int port_nbr,std::string str);
		void	config_server();
		void	AcceptNewClient();
		void	ReceiveClientData(int fd);
		void	RemoveClient(int fd);
		void	CloseConnections();
		// void	acceptconnection();
		// void	receivemessage();
		// void	sendmessage(char *message);
		~Server();
};

#endif