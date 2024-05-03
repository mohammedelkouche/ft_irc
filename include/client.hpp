/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/03 22:20:32 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>


class   Client
{
	private :
		int	fd;
		std::string ipaddress;
	public :
		Client();
		int get_fd();
		void set_ipAddress(std::string ip);
		// void SetIpAddress(std::string ip) { ipAddress = ip; }
		~Client();
};

// Client::Client()
// {}

// int	Client::get_fd()
// {
// 	return(fd);
// }

// void	Client::set_ipAddress(std::string ip)
// {
// 	this->ipaddress = ip;
// }
// Client::~Client()
// {}

#endif