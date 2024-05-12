/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/12 01:51:30 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/client.hpp"
#include "../include/reply.hpp"

//------------------------- question -------------------------------
// if we have password server " q w" if we send  pass " q w" in nc  ?
//------------------------- question -------------------------------


// Optionally, a literal asterisk character ('*', 0x2A) to indicate that the user is a server operator.
void	Server::handle_pass(Client *user)
{
	// handle " q w"	
	std::vector<std::string> commande = user->get_commande();
	if (user->get_commande().size() == 1)
	{
		if (user->is_enregistred())
			// std::cout << ": Not enough parameters" << std::endl;
			ERR_NEEDMOREPARAMS(user->get_nickname(), "PASS");
		else
			// std::cout <<": Not enough parameters" << std::endl;
			ERR_NEEDMOREPARAMS(" * ", "PASS");
	}
	else if(user->get_commande().size() == 2)
	{
		// if(this->pass == user->get_commande())
		if (user->is_enregistred())
			ERR_ALREADYREGISTERED(user->get_nickname(), "PASS");
		else
		{
			if(this->pass != commande[1])
				ERR_PASSWDMISMATCH(" * ", "PASS");
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
		if (it->get_nickname().compare(nickname))
			return (false);
	}
	return (true);
}

void	Server::handle_nickname(Client *user)
{
	std::vector<std::string> commande = user->get_commande();
	// nickname is already in use on the network ERR_NICKNAMEINUSE 
	if (user->get_commande().size() == 1)
	{
		if (user->is_enregistred())
			// std::cout << ": Not enough parameters" << std::endl;
			ERR_NEEDMOREPARAMS(user->get_nickname(), "NICK");
		else
			// std::cout <<": Not enough parameters" << std::endl;
			ERR_NEEDMOREPARAMS(" * ", "NICK");
	}
	else
	{
		// check first if he enter pssword correct ?
		//{ here }
		if (!unique_nickname(commande[1]))
			ERR_NICKNAMEINUSE(" * ", "NICK");
		else
		{
			// test
			// user->set_nickname(commande[1]);
		}
	}
}