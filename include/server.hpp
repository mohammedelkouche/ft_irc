/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/06/06 22:08:18 by oredoine         ###   ########.fr       */
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
#include "./channels.hpp"
#include <ctime>
// #include <map>


#define BUFFER_SIZE 1024

class Channel;
class Client;

class Server
{
	private :
		int port;
		std::string pass;
		int fd_srv_socket;
		std::vector<Client> clients;
		std::vector<Channel> channels;
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
		void	sendToClient(int fd, const std::string& message);
		void	CloseConnections();
		
		// handel cmd
		void	handle_pass(Client *user);
		void	handle_nickname(Client *user);
		void	handle_username(Client *user);
		void	handle_Unknown_command(Client *user);
		bool 	channelExists(std::vector<Channel> haystack, std::string needle);
		void 	JoinConstruction(Client *client);
		void 	InviteConstruction(Client *client);
		std::vector<Client> getClientsInServer();
		std::vector<Channel>  getChannelsInServer();
		void 	sendMessageToClient(Client *client, std::string message);
		// serChannels utils
		bool	unique_nickname(std::string nickname);
		bool	check_valid_nick_name(std::string nick_name);
		void	success_connect(Client *user);
		// void	check_registration(Client *user);

		~Server();
		//

};

#endif