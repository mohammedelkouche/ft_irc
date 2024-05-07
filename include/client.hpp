/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/07 22:17:39 by mel-kouc         ###   ########.fr       */
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
		void	set_fd(int fd_client);
		int		get_fd();
		// Client	*get_connect_client(int fd);
		void	set_ipAddress(std::string ip);
		~Client();
};

#endif