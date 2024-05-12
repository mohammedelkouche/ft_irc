/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:05:25 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/12 00:46:08 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/server.hpp"
// #include "../include/client.hpp"

#ifndef	REPLY_HPP
#define REPLY_HPP

#include <iostream>


// for password
void	ERR_NEEDMOREPARAMS(std::string nick_name, std::string commande)
{
	std::cout << "461 " <<  nick_name << " " << commande <<  " : Not enough parameters" << std::endl;
}
void	ERR_PASSWDMISMATCH(std::string nick_name, std::string commande)
{
	std::cout << "464 " <<  nick_name << " " << commande <<  " :Password incorrect" << std::endl;
}

void	ERR_ALREADYREGISTERED(std::string nick_name, std::string commande)
{
	std::cout << "462 " <<  nick_name << " " << commande <<  " :You may not reregister" << std::endl;
}

void	ERR_NICKNAMEINUSE(std::string nick_name, std::string commande)
{
	std::cout << "432 " <<  nick_name << " " << commande <<  " :Nickname is already in use" << std::endl;
}



#endif