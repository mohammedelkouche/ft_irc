/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:13 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/20 16:56:52 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
// #include <arpa/inet.h>

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
		~Server();
};