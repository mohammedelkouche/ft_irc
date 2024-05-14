/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:07:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/14 19:19:39 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/server.hpp"
#include "../include/client.hpp"
#include <unistd.h>


Client::Client() : ipaddress(""), nickname(""), username ("")
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

Client::~Client()
{
	
}

// void	Client::check_registre(std::string nick)
// {
// 	std::cout << " : nick = "<< nick << std::endl;
// 	if (nick.compare(""))
// 	{
// 		this->registred = true;
// 	}
// }