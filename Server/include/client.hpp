/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/11 20:43:46 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include "../../includes/Join.hpp"

class Join;

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

#endif