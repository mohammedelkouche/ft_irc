/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/23 19:00:58 by mel-kouc         ###   ########.fr       */
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

class Server
{
	private :
		int port;
		std::string pass;
	public :
		Server();
		Server(const Server &obj);
		Server& operator = (const Server &obj);
		void	run_server();
		void	config_server(int port_nbr,std::string str);
		~Server();
};