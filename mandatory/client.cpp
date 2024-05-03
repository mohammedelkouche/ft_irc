/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:01 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/03 23:27:22 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/client.hpp"

Client::Client()
{}

int	Client::get_fd()
{
	return(fd);
}

void	Client::set_ipAddress(std::string ip)
{
	this->ipaddress = ip;
	// std::cout << this->ipaddress << std::endl;
}

Client::~Client()
{}