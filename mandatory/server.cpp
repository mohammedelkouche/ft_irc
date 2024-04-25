/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:21 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/25 19:03:46 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

// const int PORT = 8080;
// const int MAX_CLIENTS = 5;
// const int BUFFER_SIZE = 1024;

// int main(int argc, char **argv)
// {
//     // creat socket
//     int serversocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serversocket == -1)
//     {
//         std::cout << "Error could not creat socket \n";
//         // std::cerr << "Error could not creat socket \n";
//         return (1);
//     }
//     // bind the socket to an IP addres and port
//     // sockaddr_in serverAddress;
//     // struct sockaddr_in serverAddress;

//     return (0);
// }

void	Server::config_server(int port_nbr,std::string str)
{
	this->port = port_nbr;
	this->pass = str;
	
	// variable
	int fd_socket;
	struct sockaddr_in server_addr;
	
	if (fd_socket = socket(AF_INET, SOCK_STREAM, 0) == -1)
		throw "socker creation error";
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd_socket, (struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
		throw "Binding error";
	if (listen(fd_socket,SOMAXCONN) == -1)
		throw "listening error";
	
}