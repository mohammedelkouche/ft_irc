/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/27 16:44:54 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <iostream>

#define BUFFER_SIZE 1024

class Server
{
	private :
		int port;
		std::string pass;
		int fd_s_socket;
		int fd_c_socket;
		char buffer[BUFFER_SIZE];
	public :
		Server();
		Server(const Server &obj);
		Server& operator = (const Server &obj);
		void	run_server();
		void	config_server(int port_nbr,std::string str);
		void	acceptconnection();
		void	receivemessage();
		void	sendmessage(char *message);
		~Server();
};