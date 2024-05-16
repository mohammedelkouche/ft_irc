/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/16 01:36:57 by oredoine         ###   ########.fr       */
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
#include "client.hpp"
#include "channels.hpp"
#include <map>

#define BUFFER_SIZE 1024

class Channels;
class Server
{
	private :
		int port;
		std::string pass;
		int fd_srv_socket;
		std::vector<Client> clients;
		std::vector<Channels> channels;
		// Client*	user;
		
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
		void	parse_message(std::string buffer, int fd);
		Client	*get_connect_client(int fd);
		void	execute_commande(Client *user);
		void	handle_pass(Client *user);
		void	CloseConnections();
		
		// void	acceptconnection();
		// void	receivemessage();
		void JoinConstruction(Client *client);
		void InviteConstruction(Client *client);
		// void	sendmessage(char *message);
		~Server();
		//

};

#endif