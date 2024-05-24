/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/24 14:58:46 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/client.hpp"
#include "../include/reply.hpp"


// (':', 0x3A) character, in which case that character is stripped and
// the rest of the message is treated as the final parameter, including 
// any spaces it contains. Parameters that contain spaces, are empty, or
// begin with a ':' character MUST be sent with a preceding ':'; in other
//   cases the use of a preceding ':' on the final parameter is OPTIONAL.



// Optionally, a literal asterisk character ('*', 0x2A) to indicate that the user is a server operator.
void	Server::handle_pass(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	std::vector <std::string>::iterator it = std::find(commande.begin(), commande.end(), ":");
	if (it != commande.end())
		commande.erase(it);
	if (commande.size() == 1)
	{
		if (user->is_enregistred())
		{
			sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
			// ERR_NEEDMOREPARAMS(user->get_nickname(), "PASS", user->get_fd());
		}
		else
		{
			sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(" * ", user->get_hostname()));
			// ERR_NEEDMOREPARAMS(" * ", "PASS", user->get_fd());
		}
	}
	else
	{
		if (user->is_enregistred())
		{
			sendToClient(user->get_fd(), ERROR_ALREADYREGISTERED(user->get_nickname(), user->get_hostname()));
			// ERR_ALREADYREGISTERED(user->get_nickname(), "PASS", user->get_fd());
		}
		else
		{
			if(this->pass != commande[1])
			{
				sendToClient(user->get_fd(), ERROR_PASSWDMISMATCH(" * ", user->get_hostname()));
				// ERR_PASSWDMISMATCH(" * ", "PASS", user->get_fd());
			}
			else
				user->set_pass_client(commande[1]);
		}
	}
}


// void	Server::sendToClient(int fd, const std::string message)
void	Server::sendToClient(int fd, const std::string& message)
{
	// throw exception if send = -1;
	std::cout <<  "this is the message : " << message;
	if (send(fd, message.c_str(), message.length(), 0) == -1)
		throw std::runtime_error("Failed to send message");
}

void	Server::handle_nickname(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	// -------- old ---------
	// std::vector <std::string>::iterator iter = std::find(commande.begin(), commande.end(), ":");
	// if (iter != commande.end())
	// 	commande.erase(iter);
	// -------- old ---------
	// ------ new ------
	std::vector<std::string>::iterator iter = commande.begin();
	while (iter != commande.end())
	{
        if (*iter == ":" || *iter == "") {
            iter = commande.erase(iter);
        } else {
            ++iter;
        }
    }
	// ------ new ------
	
	// test
	//-------------
	std::vector<std::string>::iterator it;
	for (it = commande.begin(); it != commande.end(); ++it) {
        std::cout << "this commande 2 = |"  << *it <<"|" << std::endl;
    }
	//-------------
	std::cout <<  "size : " << commande.size() << std::endl;
	// test
	if (commande.size() == 1)
	{
		std::cout <<  "hayyyyyyyyyyyy: " <<std::endl;
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_NONICKNAMEGIVEN(user->get_nickname(), user->get_hostname()));
		else
			sendToClient(user->get_fd(), ERROR_NONICKNAMEGIVEN(" * ", user->get_hostname()));
	}
	else
	{
		std::cout <<  "Bayyyyyyyyyyyy: " <<std::endl;
		if (!user->get_pass_client().compare(""))
		{
			sendToClient(user->get_fd(), ERROR_NOTREGISTERED(" * ", user->get_hostname()));
		}
		else if (!user->is_enregistred())
		{
			if (check_valid_nick_name(commande[1]))
			{
				if (!user->get_nickname().compare(commande[1]))
					user->set_nickname(commande[1]);
				else if (!unique_nickname(commande[1]))
					sendToClient(user->get_fd(), ERROR_NICKNAMEINUSE(" * ", user->get_hostname()));
				else
					user->set_nickname(commande[1]);
			}
			else
				sendToClient(user->get_fd(), ERROR_ERRONEUSNICKNAME(" * ", user->get_hostname()));
		}
		else if (user->is_enregistred())
		{
			if (check_valid_nick_name(commande[1]))
			{
				// add the first condition
				if (!user->get_nickname().compare(commande[1]))
					user->set_nickname(commande[1]);
				else if (!unique_nickname(commande[1]))
					sendToClient(user->get_fd(), ERROR_NICKNAMEINUSE(user->get_nickname(), user->get_hostname()));
				else
				{
					sendToClient(user->get_fd(), REPLY_NICKCHANGE(user->get_nickname(), commande[1], user->get_hostname()));
					user->set_nickname(commande[1]);
				}
			}
			else
				sendToClient(user->get_fd(), ERROR_ERRONEUSNICKNAME(" * ", user->get_hostname()));
		}
	}
}

void	Server::handle_username(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	std::vector <std::string>::iterator it = std::find(commande.begin(), commande.end(), ":");
	if (it != commande.end())
		commande.erase(it);
	if (commande.size() < 5)
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
		else
			sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(" * ", user->get_hostname()));
	}
	else if (!user->get_pass_client().compare(""))
	{
		sendToClient(user->get_fd(), ERROR_NOTREGISTERED(" * ", user->get_hostname()));
	}
	else if (user->is_enregistred())
		sendToClient(user->get_fd(), ERROR_ALREADYREGISTERED(user->get_nickname(), user->get_hostname()));
	else
		user->set_username(commande[1]);
}

void	Server::handle_Unknown_command(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	if (user->is_enregistred())
		sendToClient(user->get_fd(), ERROR_UNKNOWNCOMMAND(user->get_nickname(), user->get_hostname(), commande[0]));
	else
		sendToClient(user->get_fd(), ERROR_UNKNOWNCOMMAND(" * ", user->get_hostname(), commande[0]));
}