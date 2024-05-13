/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/13 22:54:04 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/client.hpp"
#include "../include/reply.hpp"

//------------------------- question -------------------------------
// if we have password server " q w" if we send  pass " q w" in nc  ?
// password hello  -> pass hello world 
//------------------------- question -------------------------------

// (':', 0x3A) character, in which case that character is stripped and
// the rest of the message is treated as the final parameter, including 
// any spaces it contains. Parameters that contain spaces, are empty, or
// begin with a ':' character MUST be sent with a preceding ':'; in other
//   cases the use of a preceding ':' on the final parameter is OPTIONAL.

// ERR_NOTREGISTERED (451) 
  	// "<client> :You have not registered"


// Optionally, a literal asterisk character ('*', 0x2A) to indicate that the user is a server operator.
void	Server::handle_pass(Client *user)
{
	// handle " q w"	
	std::vector<std::string> commande = user->get_commande();
	if (user->get_commande().size() == 1)
	{
		if (user->is_enregistred())
			// std::cout << ": Not enough parameters" << std::endl;
			ERR_NEEDMOREPARAMS(user->get_nickname(), "PASS", user->get_fd());
		else
			// std::cout <<": Not enough parameters" << std::endl;
			ERR_NEEDMOREPARAMS(" * ", "PASS", user->get_fd());
	}
	// else if(user->get_commande().size() == 2)
	else
	{
		// if(this->pass == user->get_commande())
		if (user->is_enregistred())
			ERR_ALREADYREGISTERED(user->get_nickname(), "PASS", user->get_fd());
		else
		{
			if(this->pass != commande[1])
				ERR_PASSWDMISMATCH(" * ", "PASS", user->get_fd());
			else
				user->set_pass_client(commande[1]);
			// 	std::cout <<": what can do here ? " << std::endl;
				// ERR_PASSWDMISMATCH(" * ", "PASS");
		}
	}
}

bool	Server::unique_nickname(std::string nickname)
{
	for (std::vector<Client>::iterator it  = clients.begin(); it != clients.end(); it++)
	{
		if (!it->get_nickname().compare(nickname))
		{
			std::cout << "get_nickname = " <<  it->get_nickname() << std::endl;
			std::cout << "string nickname :" << nickname << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	Server::check_valid_nick_name(std::string nick_name)
{
	if (isdigit(nick_name[0]))
		return false;
	if (size_t test =  nick_name.find_first_of("#: ") != std::string::npos)
		return false;
	if (nick_name.find("#&") != std::string::npos)
		return false;
	if (nick_name.find("&#") != std::string::npos)
		return false;
	return true;
}

// std::string getHostname() {
//     char hostname[256]; // Buffer to hold the hostname
//     if (gethostname(hostname, sizeof(hostname)) == 0) {
//         return std::string(hostname); // Convert the C-style string to std::string
//     } else {
//         return "Unknown"; // Return "Unknown" if gethostname fails
//     }
// }

#include <netdb.h>

std::string getHostname() {
    char hostname[256]; // Buffer to hold the hostname
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        struct hostent* hostInfo = gethostbyname(hostname);
        if (hostInfo != NULL) {
            return std::string(hostInfo->h_name); // Convert the C-style string to std::string
        }
    }
    return "Unknown"; // Return "Unknown" if gethostname or gethostbyname fails
}

void	Server::sendToClient(int fd, const std::string& message)
{
	send(fd, message.c_str(), message.length(), 0);
}

void	Server::handle_nickname(Client *user)
{
	std::cout << "getHostname = " <<  getHostname() << std::endl;
	std::vector<std::string> commande = user->get_commande();
	// nickname is already in use on the network ERR_NICKNAMEINUSE 
	if (user->get_commande().size() == 1)
	{
		if (user->is_enregistred())
			ERR_NONICKNAMEGIVEN(user->get_nickname(), user->get_fd());
			// std::cout << ": Not enough parameters" << std::endl;
			// ERR_NEEDMOREPARAMS(user->get_nickname(), "NICK");
		else
			ERR_NONICKNAMEGIVEN(" * ", user->get_fd());
			// std::cout <<": Not enough parameters" << std::endl;
			// ERR_NEEDMOREPARAMS(" * ", "NICK");
	}
	else
	{
		// check first if he enter pssword correct ?
		// ERR_NOTREGISTERED
		
		if (user->get_pass_client().compare(""))
			ERR_NOTREGISTERED(" * ", "NICK", user->get_fd());
		//{ here }
		// user->is_enregistred()
		// check nickname
		if (!check_valid_nick_name(commande[1]))
		{
			// std::cout << " : hay is not valid" << std::endl;
			if (!user->is_enregistred())
			{
				if (!unique_nickname(commande[1]))
					ERR_NICKNAMEINUSE(" * ", "NICK", user->get_fd());
				else
					user->set_nickname(commande[1]);
			}
			// else if (user->is_enregistred())
			// {
				
			// }
		}
			
		// else
		// {
			// test
			// user->set_nickname(commande[1]);
		// }
	}
}