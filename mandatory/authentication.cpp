/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:36 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/16 20:38:00 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/client.hpp"
#include "../include/reply.hpp"


// Optionally, a literal asterisk character ('*', 0x2A) to indicate that the user is a server operator.
void	Server::handle_pass(Client *user)
{
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
		if(this->pass == commande[1])
			std::cout <<  "yes is mutsh" << std::endl;
		else
			std::cout <<  "no is is not matsh" << std::endl;
	}
}