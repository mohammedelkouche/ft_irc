/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/09 18:11:24 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <vector>
#include <map>
#include <netdb.h>
#include <unistd.h>
#include "global.hpp"
#include <arpa/inet.h>
#include <netdb.h>

class   Client
{
	private :
		int							fd;
		std::string 				ipaddress;
		std::vector<std::string> 	commande;
		std::string 				nickname;
		std::string 				pass_client;
		std::string 				username;
		std::string 				hostname;
		std::map<std::string, bool> invitedChannels;
		bool						registred;
		bool						isOperator;
		bool 						correct_pass;
	public :
		Client();
		Client(const Client& copy);
		~Client();
		void						set_fd(int fd_client);
		void						set_commande(std::vector <std::string> &cmd);
		void						set_nickname(std::string nick);
		void						set_pass_client(std::string password);
		void						set_username(std::string user);
		void						set_ipAddress(std::string ip);
		void						set_hostname(std::string host);
		void						setOperatorStatus(bool status);
		void						set_correct_pass(bool stat_pass);
		bool						is_enregistred();
		std::vector<std::string>	get_commande();
		int							get_fd();
		std::string					get_nickname();
		std::string					get_username();
		std::string					get_pass_client();
		std::string					get_hostname();
		std::string					get_client_host();
		bool						getIsOperatorStatus();
		std::vector<std::string>	getAccessedChannels();
		bool						check_registration(Client *user);
		bool						get_correct_pass();
		std::map<std::string, bool> &getInvitedChannels();
};

#endif