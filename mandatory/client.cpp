/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:07:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/10 16:33:04 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/server.hpp"
#include "../include/client.hpp"
#include <iostream>
Client::Client()
{
	this->registred = false;
}

void	Client::set_fd(int fd_client)
{
	this->fd  = fd_client;
}

int    Client::get_fd()
{
	return this->fd;
}

bool	Client::is_enregistred()
{
	return this->registred;
}
void	Client::set_commande(std::vector <std::string> &cmd)
{
	this->commande = cmd;
}

std::vector<std::string>	Client::get_commande()
{
	return this->commande;
}

void	Client::set_nickname(std::string nick)
{
	this->nickname = nick;
}
void	Client::set_username(std::string user)
{
	this->username = user;
}

std::string	Client::get_nickname()
{
	return this->nickname;
	
}

std::string	Client::get_username()
{
	return this->username;
}


void    Client::set_ipAddress(std::string ip)
{
	this->ipaddress = ip;
}


Client::~Client()
{
	
}
