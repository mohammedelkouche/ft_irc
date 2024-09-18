/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:07:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/14 00:39:27 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"
#include <iostream>


Client::Client() : ipaddress(""), nickname(""), pass_client(""), username (""), isOperator(false),correct_pass(false),isdelimiter(false), saveData("")
{
	this->registred = false;
}

Client::Client(const Client& copy)
{
	fd = copy.fd;
	pass_client = copy.pass_client;
	ipaddress = copy.ipaddress;
	nickname = copy.nickname;
	username = copy.username;
	hostname = copy.hostname;
	registred = copy.registred;
	isOperator = copy.isOperator;
	correct_pass = copy.correct_pass;
	isdelimiter = copy.isdelimiter;
	commande = copy.commande;
	invitedChannels = copy.invitedChannels;
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


void	Client::set_nickname(std::string nick)
{
	this->nickname = nick;
}
void	Client::set_username(std::string user)
{
	this->username = user;
}
void    Client::set_ipAddress(std::string ip)
{
	this->ipaddress = ip;
}
void	Client::set_pass_client(std::string password)
{
	this->pass_client = password;
}

void	Client::set_hostname(std::string host)
{
	this->hostname = host;
}

void	Client::setOperatorStatus(bool status)
{
	this->isOperator = status;
}

void	Client::set_correct_pass(bool stat_pass)
{
	this->correct_pass = stat_pass;
}

bool	Client::getIsOperatorStatus()
{
	return this->isOperator;
}

std::vector<std::string>	Client::get_commande()
{
	return this->commande;
}

std::string	Client::get_pass_client()
{
	return this->pass_client;
}
std::string	Client::get_nickname()
{
	return this->nickname;
	
}

std::string	Client::get_username()
{
	return this->username;
}

std::string	Client::get_hostname()
{
	return this->hostname;
}

bool	Client::get_correct_pass()
{
	return this->correct_pass;
}

bool	Client::check_registration(Client *user)
{

	if (!user->registred && user->get_pass_client().compare("")   && user->get_nickname().compare("") && user->get_username().compare(""))
	{
		user->registred = true;
		return true;
	}
	else
		return false;
}

std::string Client::get_client_host()
{
    struct in_addr addr;
    inet_aton(ipaddress.c_str(), &addr);

    struct hostent* hostInfo = gethostbyaddr((const void*)&addr, sizeof(addr), AF_INET);
    if (hostInfo != NULL)
        return std::string(hostInfo->h_name);
    return "Unknown";
}

std::map<std::string, bool>& Client::getInvitedChannels()
{
	return this->invitedChannels;
}

Client::~Client()
{
	
}