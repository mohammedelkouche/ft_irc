#include "../include/server.hpp"

Server::Server()
{
	
}

// void	Server::acceptconnection()
// {
// 	struct sockaddr_in client_addr;
// 	socklen_t client_addr_len = sizeof(client_addr);
// 	this->fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
// 	if (fd_c_socket == -1)
// 		throw "Accept error";
// }

// void Server::receivemessage()
// {
// 	int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, 0);

// 	if (bytes_read <= 0)
// 		throw ("Connection closed by client");
// 	buffer[bytes_read] = '\0';
// 	std::cout << "Client: " << buffer << std::endl;
	
// 	//--------------- UPDATE -----------------
// 	// int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, MSG_DONTWAIT); // Use MSG_DONTWAIT to make recv non-blocking
// 	// if (bytes_read > 0) {
//     //         buffer[bytes_read] = '\0';
//     //         std::cout << "Client: " << buffer << std::endl;
//     //     } else if (bytes_read == 0) {
//     //         throw "Connection closed by client";
//     //     }
// }
// void	Server::sendmessage(char *message)
// {
// 	if (send(fd_c_socket, message, strlen(message), 0) == -1) {
// 		throw "Send error";
// 	}
	
// 	//--------------- UPDATE -----------------
// 	// if (send(fd_c_socket, message, strlen(message), MSG_DONTWAIT) == -1) {
// 	// 	throw "Send error";
// 	// }
// }
// void	Server::config_server()
// {
// 	this->port = port_nbr;
// 	this->pass = str;
	
// 	struct sockaddr_in server_addr;
	
// 	this->fd_s_socket = socket(AF_INET, SOCK_STREAM, 0);
// 	if (fd_s_socket == -1)
// 		throw "socker creation error";
// 	memset(&server_addr, 0, sizeof(server_addr));
// 	server_addr.sin_family = AF_INET;
// 	server_addr.sin_port = htons(this->port);
// 	server_addr.sin_addr.s_addr = INADDR_ANY;
// 	if (bind(fd_s_socket, (struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
// 		throw "Binding error";
// 	if (listen(fd_s_socket,SOMAXCONN) == -1)
// 		throw "listening error";
// }

void	Server::config_server()
{
	struct sockaddr_in server_addr;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	fd_srv_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_srv_socket == -1)
		throw(std::runtime_error("Failed to create socket"));
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
	clients.push_back(newclient);
	pollfds.push_back(client_poll_fd);
	std::cout << "Client <" << fd_client_sock << "> Connected" << std::endl;
}

void	Server::RemoveClient(int fd)
{
	for (size_t i = 0; i < pollfds.size(); i++)
	{
		if (pollfds[i].fd == fd)
		{
			pollfds.erase(pollfds.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < pollfds.size(); i++)
	{
		if (clients[i].get_fd() == fd)
		{
			clients.erase(clients.begin() + i);
			break ;
		}
	}
}

void	Server::ReceiveClientData(int fd)
{
	memset(buffer, 0 , BUFFER_SIZE);
	size_t bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received <= 0)
	{
		 std::cout << "Client <" << fd << "> Disconnected" << std::endl;
        RemoveClient(fd);
        close(fd);
	}
	else
	{
		buffer[bytes_received] = '\0';
		std::cout << "Client <" << fd << "> Data: " << buffer;
	}
}

void	Server::initializeServer(int port_nbr,std::string str)
{
	this->port = port_nbr;
	this->pass = str;
	config_server();

	std::cout << "Server with fd <" << fd_srv_socket << "> Connected" << std::endl;
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