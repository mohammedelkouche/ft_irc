/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:08:51 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/08 23:58:06 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

Server::Server()
{
	
}

void	Server::config_server()
{
	int enable = 1;
	struct sockaddr_in server_addr;
	
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
	
	struct pollfd server_poll_fd;
	server_poll_fd.fd = fd_srv_socket;
	server_poll_fd.events = POLLIN;
	// clearing any previous events that might have been stored in that member.
	// ensuring that it doesn't carry over any previous events from previous
	// poll() calls. This prepares it to store the new events detected by
	// the next poll() call.
	server_poll_fd.revents = 0;
	pollfds.push_back(server_poll_fd);
}

void	Server::AcceptNewClient()
{
	Client	newclient;

	struct sockaddr_in client_addr;
	socklen_t addresslenght = sizeof(client_addr);

	int fd_client_sock = accept(fd_srv_socket, (sockaddr *)&client_addr, &addresslenght);
	if (fd_client_sock == -1)
	{
		 std::cout << "accept() failed" << std::endl;
        return;
    }
	if (fcntl(fd_client_sock, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
        return;
	}
	
	struct pollfd client_poll_fd;
	client_poll_fd.fd = fd_client_sock;
	client_poll_fd.events = POLLIN;
	client_poll_fd.revents = 0;

	newclient.set_ipAddress(inet_ntoa(client_addr.sin_addr));
	newclient.set_fd(fd_client_sock);
	// for vector
	// clients.insert(std::make_pair(fd_client_sock, newclient));
	
	// for vector
	clients.push_back(newclient);
	pollfds.push_back(client_poll_fd);
	std::cout << "Client fd = '" << fd_client_sock << "' Connected" << std::endl;
}

void	Server::RemoveClient(int fd)
{
	// Erase the client from the map
    // clients.erase(fd);
	
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
}

std::vector<std::string>	devide_commande(std::string message, int fd)
{
	std::vector<std::string> vector;
	(void)fd;
	// int	flag = 0;
	std::string Command;
	for (size_t space = 0; space < message.size(); space++)
	{
		
		// if (message[0] == ':' && flag == 0)
		// {
		// 	vector.push_back(message.substr(0,1));
		// 	flag = 1;
		// }
		if (!std::isspace(message[space]))
		{
			size_t	next_space = message.find(' ', space);
			if (message[space] == ':')
				vector.push_back(message.substr(space,1));
			else if (next_space != std::string::npos)
			{
				vector.push_back(message.substr(space, next_space - space));
				space = next_space;
			}
			else
			{
				vector.push_back(message.substr(space, message.size() - space));
				break ;
			}
		}
	}
	// for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); ++it)
    // {
    //     std::cout << "it  = <" << *it << ">" << std::endl;
    // }
	return vector;
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

void	Server::parse_message(std::string buffer, int fd)
{
	std::vector <std::string> commande;
	std::string message;
	Client	*user = get_connect_client(fd);
	if (user)
		std::cout << "hello" << std::endl;
	// size_t	pos = buffer.find_first_of("\r\n");
	// size_t	pos = buffer.find("ou");
	// size_t	pos = buffer.find("\n");
	size_t	pos = buffer.find("\r\n");
	// std::cout << "pos = '" << pos << std::endl;
	if (pos != std::string::npos)
	{
		message = buffer.substr(0, pos);
		// std::cout << "test = '" << message << std::endl;
		commande = devide_commande(message, fd);
		user->set_commande(commande);
		execute_commande(user);
		for (std::vector<std::string>::iterator it = commande.begin(); it != commande.end(); ++it)
		{
			std::cout << "it  = <" << *it << ">" << std::endl;
		}
	}
	else
		std::cout << "we don't found \n\r  " << std::endl;
}

void	Server::ReceiveClientData(int fd)
{
	memset(buffer, 0 , BUFFER_SIZE);
	size_t bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received <= 0)
	{
		std::cout << "Client fd = '" << fd << "' Disconnected" << std::endl;
        RemoveClient(fd);
        close(fd);
	}
	else
	{
		buffer[bytes_received] = '\0';
		std::cout << "Client fd = '" << fd << "' send : " << buffer;
		parse_message(buffer,fd);
	}	
}

void	Server::initializeServer(int port_nbr,std::string str)
{
	this->port = port_nbr;
	this->pass = str;
	config_server();

	std::cout << "Server with fd <" << fd_srv_socket << "> Connected" << std::endl;
	std::cout << "Server started. Listening on port : " << this->port << std::endl;
	std::cout << "Waiting to accept a connection...\n";
	
	while (true)
	{
		if (poll(&pollfds[0], pollfds.size(), -1) == -1)
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
}


Server::~Server()
{
}