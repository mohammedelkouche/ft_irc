/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/03 19:05:19 by oredoine         ###   ########.fr       */
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
#include "global.hpp"
#include <map>


#define BUFFER_SIZE 1024

class Channel;
class Client;

class Server
{
	private :
		int							port;
		std::string 				pass;
		int 						fd_srv_socket;
		std::vector<Client> 		clients;
		std::vector<Channel *> 		channels;
		std::vector <struct pollfd> pollfds;
		std::map<int, std::string> 	partial_messages; // To store incomplete messages
		// char buffer[BUFFER_SIZE];
		static bool 				stopServer;
		struct sockaddr_in 			server_addr;
		struct sockaddr_in 			client_addr;
		struct pollfd 				client_poll_fd;
	public :
		Server();
		Server(const Server &obj);
		Server& operator = (const Server &other);
		~Server();
		void					initializeServer(int port_nbr,std::string str);
		void					config_server();
		void					AcceptNewClient();
		void					ReceiveClientData(int fd);
		void					RemoveClient(int fd);
		void					parse_message(std::string buffer, int fd);
		Client					*get_connect_client(int fd);
		void					execute_commande(Client *user);
		// void	sendToClient(int fd, const std::string message);
		void					sendToClient(int fd, const std::string& message);
		void					close_all_fds();
		
		// handel cmd
		void					handle_pass(Client *user);
		void					handle_nickname(Client *user);
		void					handle_username(Client *user);
		void					handle_Unknown_command(Client *user);
		bool 					channeDoesntlExists(std::vector<Channel *> haystack, std::string needle);
		// cmd construction
		void 					JoinConstruction(Client *client);
		void 					InviteConstruction(Client *client);
		void 					KickConstruction(Client *client);
		void					PartConstruction(Client *client);
		//cmd utils (oussama)
		Client& 				getClientByNick(std::vector<Client> &clients, std::string nickname);
		std::vector<Channel *>  &getChannelsInServer();
		std::vector<Client> 	getClientsInServer();
		bool 					isClientExist(std::vector<Client> clients, std::string nickname);
		std::string 			buildNamReply(Channel *channel);
		void 					selfJoinReply(Client *client, Channel *channel);
		void 					updateClientsOnTheChannel(Client *client, std::string newNick);
		void 					joinZeroo(Client *client);
		void 					broadcastWithoutTargetedChannel(Client *user, std::string message);
		void 					deleteTheChannelWhenNoUserInIt(Channel *channel);
		// server utils		
		bool					unique_nickname(std::string nickname);
		bool					check_valid_nick_name(std::string nick_name);
		void					success_connect(Client *user);
		Channel* 				getChannelByName(std::vector<Channel *> channels, std::string name);
		// add
		bool					check_valid_realname(std::string realname);
		static void 			handleSigint(int sig);
		/*                        AYGAOUA SPEAKING                        */
		/*------------------------TOPIC COMMAND---------------------------*/
		void					Topic_Command(std::vector<std::string> Topic, Client *user);
		void					DisplayTopic(std::vector<std::string> channel_name, Client *user);
		int						no_suck_channel(std::vector<std::string> Topic);
		int						on_channel(std::vector<Client *>  Clnts, Client *nick);
		/*----------------------------------------------------------------*/

		/*------------------------PRIVMSG COMMAND---------------------------*/
		void					Private_message(std::vector<std::string> command, Client *user);
		void					sendToChannel(Client *user, const std::string& message, std::string Chnl);
		int						no_suck_channel_msg(std::string chnl);
		/*----------------------------------------------------------------*/

		/*------------------------PRIVMSG COMMAND---------------------------*/
		void					ModeCommand(std::vector<std::string> command, Client *user);
		// void DisplayMode(std::vector<std::string> command, Client *user);
		/*----------------------------------------------------------------*/
		/*                        AYGAOUA SPEAKING                        */
		// void	check_registration(Client *user);

		//

};

#endif
