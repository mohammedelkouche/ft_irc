/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:08:51 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/06 00:15:35 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"
#include "../include/server.hpp"
#include "../include/reply.hpp"


Server::Server() : pass("")
{
    signal(SIGINT, handleSigint);
    signal(SIGPIPE, SIG_IGN);
}

	
Server::Server(const Server &obj)
{
	port = obj.port;
	pass = obj.pass;
	fd_srv_socket = obj.fd_srv_socket;
	for(size_t i = 0; i < clients.size(); i++)
        	clients[i] = obj.clients[i];
	for(size_t i = 0; i < channels.size(); i++)
        	channels[i] = obj.channels[i];
}

Server &Server::operator=(Server const &other){
	if (this != &other)
	{
		this->fd_srv_socket = other.fd_srv_socket;
		this->port = other.port;
		this->pass = other.pass;
		this->clients = other.clients;
		this->pollfds = other.pollfds;
		this->channels = other.channels;
	}
	return *this;
}


void	Server::config_server()
{
	int enable = 1;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	fd_srv_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_srv_socket == -1)
		throw(std::runtime_error("Failed to create socket"));
	if (setsockopt(fd_srv_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
        throw(std::runtime_error("Failed to set option (SO_REUSEADDR) on socket"));
	if (fcntl(fd_srv_socket, F_SETFL, O_NONBLOCK)  == -1)
		throw(std::runtime_error("Failed to set option (O_NONBLOCK) on socket"));
	if (bind(fd_srv_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
		throw(std::runtime_error("Failed to bind socket"));
	if (listen(fd_srv_socket, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() failed"));
	
	client_poll_fd.fd = fd_srv_socket;
	client_poll_fd.events = POLLIN;
	client_poll_fd.revents = 0;
	pollfds.push_back(client_poll_fd);
}

void	Server::AcceptNewClient()
{
	Client	newclient;
	std::string	host;

	socklen_t addresslenght = sizeof(client_addr);

	int fd_client_sock = accept(fd_srv_socket, (sockaddr *)&client_addr, &addresslenght);
	if (fd_client_sock == -1)
	{
		//  std::cout << "accept() failed" << std::endl;
        return;
    }
	if (fcntl(fd_client_sock, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
        return;
	}
	
	client_poll_fd.fd = fd_client_sock;
	client_poll_fd.events = POLLIN;
	client_poll_fd.revents = 0;

	newclient.set_ipAddress(inet_ntoa(client_addr.sin_addr));
	newclient.set_fd(fd_client_sock);
	host = newclient.get_client_host();
	newclient.set_hostname(host);
	
	clients.push_back(newclient);
	pollfds.push_back(client_poll_fd);
	// insert a new buffer entry for the new client
	partial_messages.insert(std::make_pair(fd_client_sock, ""));
	std::string yellow = "\033[33m";
	std::string green = "\033[32m";
	std::string reset = "\033[0m";

	std::cout << yellow << " Client fd = " << fd_client_sock << reset << green << " Connected" << reset << std::endl;
}

void	Server::RemoveClient(int fd)
{

	// for vector
	for (size_t i = 0; i < pollfds.size(); i++)
	{
		if (clients[i].get_fd() == fd)
		{
			clients.erase(clients.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < pollfds.size(); i++)
	{
		if (pollfds[i].fd == fd)
		{
			pollfds.erase(pollfds.begin() + i);
			break ;
		}
	}
	partial_messages.erase(fd);  // Remove any stored partial messages for the client
}

std::vector<std::string>	devide_commande(std::string message)
{
	std::vector<std::string> vector;
	std::string Command;
	for (size_t space = 0; space < message.size(); space++)
	{
		if (!std::isspace(message[space]))
		{
			size_t	next_space = message.find(' ', space);
			size_t	next_tab = message.find('	', space);
			if (message[space] == ':')
			{
				vector.push_back(message.substr(space,1));
				vector.push_back(message.substr(space + 1, message.size() - (space + 1)));
				break ;
			}
			else if (next_space != std::string::npos || next_tab != std::string::npos)
			{
				if (next_tab < next_space)
				{
					vector.push_back(message.substr(space, next_tab - space));
					space = next_tab;
				}
				else
				{
					vector.push_back(message.substr(space, next_space - space));
					space = next_space;
				}
			}
			else
			{
				vector.push_back(message.substr(space, message.size() - space));
				break ;
			}
		}
	}
	return vector;
}


void	Server::execute_commande(Client *user)
{
	std::vector <std::string> commande;
	commande = user->get_commande();
	if (user->get_commande().empty())
		return ;
	if(commande[0] == "pong" || commande[0] == "PONG")
		return;
	if (commande[0] == "pass" || commande[0] == "PASS")
		handle_pass(user);
	else if (commande[0] == "nick" || commande[0] == "NICK")
	{
		handle_nickname(user);
		if (user->check_registration(user))
			success_connect(user);
	}
	else if (commande[0] == "user" || commande[0] == "USER")
	{
		handle_username(user);
		if (user->check_registration(user))
			success_connect(user);
	}
	if (user->is_enregistred())
	{		
		if (commande[0] == "join" || commande[0] == "JOIN")
			JoinConstruction(user);
		else if (commande[0] == "invite" || commande[0] == "INVITE")
			InviteConstruction(user);
		else if  (commande[0] == "kick" || commande[0] == "KICK")
			KickConstruction(user);
		else if  (commande[0] == "part" || commande[0] == "PART")
			PartConstruction(user);
		else if(commande[0] == "topic" || commande[0] == "TOPIC")
		{
			if (commande.size() >= 3)
				Topic_Command(commande, user);
			else
				DisplayTopic(commande, user);
		}
		else if (commande[0] == "PRIVMSG" || commande[0] == "privmsg")
			Private_message(commande, user);
		else if (commande[0] == "MODE" || commande[0] == "mode")
			ModeCommand(commande, user);
		else
			handle_Unknown_command(user);
	}
	else
		handle_Unknown_command(user);
}

void	Server::parse_message(std::string buffer, int fd)
{
	Client	*user = get_connect_client(fd);
	size_t pos = 0;
    size_t end_pos = 0;
	while ((end_pos = buffer.find("\r\n", pos)) != std::string::npos) {
		std::string command = buffer.substr(pos, end_pos - pos);
		std::vector<std::string> commande = devide_commande(command);
		user->set_commande(commande);
		execute_commande(user);
		pos = end_pos + 2; // Move past "\r\n"
	}

}

Client* Server::get_connect_client(int fd)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].get_fd() == fd)
			return (&clients[i]);
	}
	return (NULL);
}


std::vector<Client> Server::getClientsInServer()
{
	return clients;
}

std::vector<Channel *>  &Server::getChannelsInServer()
{
	return channels;
}

void	Server::ReceiveClientData(int fd)
{	
	char buffer[BUFFER_SIZE];
	std::string message;
	memset(buffer, 0 , BUFFER_SIZE);
	size_t pos = 0;
    size_t end_pos = 0;
	size_t bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
	std::string red = "\033[31m";
	std::string yellow = "\033[33m";
	std::string reset = "\033[0m";
	if (bytes_received <= 0)
	{
		std::cout << yellow << "Client fd = " << fd  << reset << red  << " Disconnected " << reset << std::endl;
		Client * client = get_connect_client(fd);
		for (size_t i = 0; i < channels.size(); i++)
		{
			channels[i]->removeFromChannel(client);
			deleteTheChannelWhenNoUserInIt(channels[i]);
		}
        RemoveClient(fd);
        close(fd);
	}
	else
	{
		if (bytes_received < BUFFER_SIZE) {
            buffer[bytes_received] = '\0';
        } else {
            buffer[BUFFER_SIZE - 1] = '\0';
        }
		message = buffer;
		if ((end_pos = message.find("\r\n", pos)) != std::string::npos)
		{
			partial_messages[fd] += message;
			parse_message(partial_messages[fd],fd);
			partial_messages[fd].clear();
		}
		else if (message.find("\n", pos) == std::string::npos)
			partial_messages[fd] += message;
	}
}

bool Server::stopServer = 0;

void Server::handleSigint(int sig)
{
	(void) sig;
    // std::cout << "Caught SIGINT (" << sig << "). Shutting down server gracefully." << std::endl;
    Server::stopServer = 1; // Set the flag to stop the server loop
}

void	Server::close_all_fds()
{
	std::string orange = "\033[38;5;208m";
	std::string red = "\033[31m";
	std::string yellow = "\033[33m";
	std::string reset = "\033[0m";

	for (size_t i = 0; i < clients.size(); i++)
	{
		std::cout << yellow << "Client fd = " << clients[i].get_fd()  << reset << red  << " Disconnected " << reset << std::endl;
		close(clients[i].get_fd());
	}
	if (fd_srv_socket != -1)
	{
		std::cout << orange << "Server fd = " << fd_srv_socket  << reset << red  << " Disconnected " << reset << std::endl;
		close(fd_srv_socket);
	}
}


void	Server::initializeServer(int port_nbr,std::string str)
{
	this->port = port_nbr;
	this->pass = str;
	config_server();
	
	// std::cout << "Server with fd <" << fd_srv_socket << "> Connected" << std::endl;
	// std::cout << "Server started. Listening on port : " << this->port << std::endl;
	// std::cout << "Waiting to accept a connection..." << std::endl;
	
	while (!stopServer)
	{
		if (poll(&pollfds[0], pollfds.size(), -1) == -1 && !stopServer)
			throw(std::runtime_error("poll() failed"));
		for (size_t i = 0; i < pollfds.size(); i++)
		{
			// check if file descriptor has data available for reading
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == fd_srv_socket)
					AcceptNewClient();
				else
					ReceiveClientData(pollfds[i].fd);
			}
		}
	}
	close_all_fds();
}


Server::~Server()
{
}


