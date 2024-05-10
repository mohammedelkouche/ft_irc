/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:07:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/04 18:12:31 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

Client::Client()
{
	
}

int    Client::get_fd()
{
    return fd;
}

void    Client::set_ipAddress(std::string ip)
{
    this->ipaddress = ip;
}



Client::~Client()
{
	
}
