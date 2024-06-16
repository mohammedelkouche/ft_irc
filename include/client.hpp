/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/06/15 21:39:28 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <vector>
#include <netdb.h>
#include <unistd.h>
#include "global.hpp"

class   Client
{
	private :
		int	fd;
		std::string ipaddress;
		std::vector<std::string> commande;
		std::string nickname;
		std::string pass_client;
		std::string username;
		std::string hostname;
		// the channels that the client invited to
		std::vector<std::string> invitedChannels;
		bool	registred;
		bool	isOperator;
	public :
		Client();
		Client(const Client& copy);
		~Client();
		void	set_fd(int fd_client);
		void	set_commande(std::vector <std::string> &cmd);
		void	set_nickname(std::string nick);
		void	set_pass_client(std::string password);
		void	set_username(std::string user);
		void	set_ipAddress(std::string ip);
		void	set_hostname(std::string host);
		void	setOperatorStatus(bool status);
		
		bool	is_enregistred();
		std::vector<std::string>	get_commande();
		int		get_fd();
		std::string	get_nickname();
		std::string	get_username();
		std::string	get_pass_client();
		std::string	get_hostname();
		std::string	get_client_host();
		bool		getIsOperatorStatus();
		std::vector<std::string>	getAccessedChannels();
		bool		check_registration(Client *user);
		// Client	*get_connect_client(int fd);
		//oussama added a vector of channels accessible by the client
		std::vector<std::string>& getInvitedChannels();
};

#endif