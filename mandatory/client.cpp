/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:07:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/24 14:39:49 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/server.hpp"
#include "../include/client.hpp"
#include <iostream>


Client::Client() : ipaddress(""), nickname(""), pass_client(""), username (""), isOperator(false),correct_pass(false)
{
	this->registred = false;
}


Client::Client(const Client& copy)
{
	fd = copy.fd;
	ipaddress = copy.ipaddress;
	nickname = copy.nickname;
	username = copy.username;
	hostname = copy.hostname;
	registred = copy.registred;
	isOperator = copy.isOperator;
	correct_pass = copy.correct_pass;
	for(size_t i = 0; i < commande.size(); i++)
		commande[i] = copy.commande[i];
	for(size_t i = 0; i < invitedChannels.size(); i++)
		invitedChannels[i] = copy.invitedChannels[i];
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
// add
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

// add
bool	Client::get_correct_pass()
{
	return this->correct_pass;
}

bool	Client::check_registration(Client *user)
{
	std::cout << "user->get_pass_client() <<" << user->get_pass_client()  << ">>" << std::endl;
	std::cout << "user->get_nickname() <<" << user->get_nickname()  << ">>" << std::endl;
	std::cout << "user->get_username() <<" << user->get_username()  << ">>" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	if (!user->registred && user->get_pass_client().compare("")   && user->get_nickname().compare("") && user->get_username().compare(""))
	{
		std::cout << "-----------  yesssssss   isssss registreeeeed   ------------" << std::endl;
		user->registred = true;
		return true;
	}
	else
		return false;
}


// gethostname is a system call that retrieves the name
// of the current machine (the host) on which your program
// is running.

std::string  Client::get_client_host() {
    char hostname[256]; // Buffer to hold the hostname
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        struct hostent* hostInfo = gethostbyname(hostname);
        if (hostInfo != NULL) {
            return std::string(hostInfo->h_name);
        }
    }
    return "Unknown";
}


std::vector<std::string>& Client::getInvitedChannels()
{
	return this->invitedChannels;
}



Client::~Client()
{
	
}