/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/27 11:43:23 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/client.hpp"
#include "../include/reply.hpp"

void	Server::handle_pass(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	
	std::vector <std::string>::iterator it = std::find(commande.begin(), commande.end(), ":");

	if (it != commande.end())
			commande.erase(it);
	if (commande.size() == 1)
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
		else
			sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(" * ", user->get_hostname()));
	}
	else
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_ALREADYREGISTERED(user->get_nickname(), user->get_hostname()));
		else
		{
			if (this->pass != commande[1])
			{
				if (user->get_correct_pass())
					sendToClient(user->get_fd(), ERROR_ALREADYSETPASS("*", user->get_hostname()));
				else
					sendToClient(user->get_fd(), ERROR_PASSWDMISMATCH(" * ", user->get_hostname()));
			}
			else
			{ 
				if (user->get_correct_pass())
				{
					sendToClient(user->get_fd(), ERROR_ALREADYSETPASS("*", user->get_hostname()));
				}
				else
				{
					user->set_pass_client(commande[1]);
					user->set_correct_pass(true);
				}
			}
		}
	}
}


void	Server::sendToClient(int fd, const std::string& message)
{
	if (send(fd, message.c_str(), message.length(), 0) == -1)
		std::cerr << "send() faild" << std::endl;
}

void	Server::handle_nickname(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	std::vector<std::string>::iterator iter = commande.begin();
	while (iter != commande.end())
	{
        if (*iter == ":" || *iter == "")
            iter = commande.erase(iter);
        else
            ++iter;
    }
	if (commande.size() == 1)
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_NONICKNAMEGIVEN(user->get_nickname(), user->get_hostname()));
		else
			sendToClient(user->get_fd(), ERROR_NONICKNAMEGIVEN(" * ", user->get_hostname()));
	}
	else
	{
		if (!user->get_correct_pass())
			sendToClient(user->get_fd(), ERROR_NOTREGISTERED(" * ", user->get_hostname()));
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
				sendToClient(user->get_fd(), ERROR_ERRONEUSNICKNAME(user->get_nickname(), user->get_hostname()));
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
	else if (commande.size() == 5)
	{
		if (!user->get_correct_pass())
		{
			sendToClient(user->get_fd(), ERROR_NOTREGISTERED(" * ", user->get_hostname()));
		}
		else if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_ALREADYREGISTERED(user->get_nickname(), user->get_hostname()));
		else if(!check_valid_realname(commande[4]))
			sendToClient(user->get_fd(), ERROR_REALNAME("*", user->get_hostname()));
		else
			user->set_username(commande[1]);
	}
	else
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_ALREADYREGISTERED(user->get_nickname(), user->get_hostname()));
		else
		{
			if (!user->get_correct_pass())
				sendToClient(user->get_fd(), ERROR_NOTREGISTERED(" * ", user->get_hostname()));
			else
				sendToClient(user->get_fd(), ERROR_TOOMUSHPARAMS("*", user->get_hostname()));
		}
	}
}

void	Server::handle_Unknown_command(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	
	// array for  enregistred client
	std::string rg_arr[20] = {"pass", "PASS",  "nick",  "NICK", "user", "USER", "join", "JOIN", "invite", "INVITE", "kick", "KICK", "part", "PART", "topic", "TOPIC", "privmsg", "PRIVMSG", "mode", "MODE"};
	std::vector <std::string> rg_cmd(rg_arr, rg_arr + sizeof(rg_arr) / sizeof(rg_arr[0]));
	std::vector<std::string>::iterator it;
	it = std::find(rg_cmd.begin(), rg_cmd.end(), commande[0]);
	
	
	//array for not enregistred client
	std::string arr_2[14] = {"join", "JOIN", "invite", "INVITE", "kick", "KICK", "part", "PART", "topic", "TOPIC", "privmsg", "PRIVMSG", "mode", "MODE"};
	std::vector <std::string> not_rg_cmd(arr_2, arr_2 + sizeof(arr_2) / sizeof(arr_2[0]));
	std::vector<std::string>::iterator iterator;
	iterator = std::find(not_rg_cmd.begin(), not_rg_cmd.end(), commande[0]);
	
	if(it == rg_cmd.end())
	{
		if (user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_UNKNOWNCOMMAND(user->get_nickname(), user->get_hostname(), commande[0]));
		else 
			sendToClient(user->get_fd(), ERROR_UNKNOWNCOMMAND(" * ", user->get_hostname(), commande[0]));
	}
	else if(iterator != not_rg_cmd.end())
	{
		if (!user->is_enregistred())
			sendToClient(user->get_fd(), ERROR_NEEDTOREGISTER(" * ", user->get_hostname(), commande[0]));
	}
}
