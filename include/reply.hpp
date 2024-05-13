/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:05:25 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/13 03:23:54 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/server.hpp"
// #include "../include/client.hpp"

#ifndef	REPLY_HPP
#define REPLY_HPP

#include <iostream>

void	ERR_NEEDMOREPARAMS(std::string nick_name, std::string commande)
{
	std::cout << "461 " <<  nick_name << " " << commande <<  " : Not enough parameters" << std::endl;
}

#endif