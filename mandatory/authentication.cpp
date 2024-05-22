/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/19 14:17:46 by mel-kouc         ###   ########.fr       */
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
	std::vector<std::string> commande = user->get_commande();
	std::vector <std::string>::iterator it = std::find(commande.begin(), commande.end(), ":");
	if (it != commande.end())
		commande.erase(it);
	if (user->get_commande().size() == 1)
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


void	Server::sendToClient(int fd, const std::string& message)
{
	// throw exception if send = -1;
	send(fd, message.c_str(), message.length(), 0);
}

void	Server::handle_nickname(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	std::vector <std::string>::iterator it = std::find(commande.begin(), commande.end(), ":");
	if (it != commande.end())
		commande.erase(it);
	if (user->get_commande().size() == 1)
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_NONICKNAMEGIVEN(user->get_nickname(), user->get_hostname()));
		else
			sendToClient(user->get_fd(), ERROR_NONICKNAMEGIVEN(" * ", user->get_hostname()));
	}
	else
	{
		if (!user->get_pass_client().compare(""))
		{
			sendToClient(user->get_fd(), ERROR_NOTREGISTERED(" * ", user->get_hostname()));
		}
		else if (!user->is_enregistred())
		{
			if (check_valid_nick_name(commande[1]))
			{
				if (!unique_nickname(commande[1]))
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
				if (!unique_nickname(commande[1]))
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
	if (user->get_commande().size() < 5)
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