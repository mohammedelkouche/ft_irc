/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/07 18:38:01 by azgaoua          ###   ########.fr       */
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
		std::vector<Channel *> channels;
		std::vector <struct pollfd> pollfds;
		char buffer[BUFFER_SIZE];
	public :
		Server();
		Server(const Server &obj);
		Server& operator = (const Server &obj);
		~Server();
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
		bool 	channeDoesntlExists(std::vector<Channel *> haystack, std::string needle);
		// cmd construction
		void 	JoinConstruction(Client *client);
		void 	InviteConstruction(Client *client);
		void 	KickConstruction(Client *client);
		void	PartConstruction(Client *client);
		//cmd utils (oussama)
		Client& getClientByNick(std::vector<Client> &clients, std::string nickname);
		std::vector<Channel *>  &getChannelsInServer();
		std::vector<Client> getClientsInServer();
		bool isClientExist(std::vector<Client> clients, std::string nickname);
		// server utils
		bool	unique_nickname(std::string nickname);
		bool	check_valid_nick_name(std::string nick_name);
		void	success_connect(Client *user);
		/*                        AYGAOUA SPEAKING                        */

		void	Topic_Command(std::vector<std::string> Topic, Client *user);
		void	DisplayTopic(std::string channel_name, Client *user);
		/*----------------------------------------------------------------*/
		// void	check_registration(Client *user);

		//

};

#endif
