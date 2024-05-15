/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/15 23:45:44 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <vector>
#include <netdb.h>
#include <unistd.h>


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
		bool registred;
	public :
		Client();
		void	set_fd(int fd_client);
		void	set_commande(std::vector <std::string> &cmd);
		void	set_nickname(std::string nick);
		void	set_pass_client(std::string password);
		void	set_username(std::string user);
		void	set_hostname(std::string host);
		
		bool	is_enregistred();
		std::vector<std::string>	get_commande();
		int		get_fd();
		std::string	get_nickname();
		std::string	get_username();
		std::string	get_pass_client();
		std::string	get_hostname();
		std::string	get_client_host();
		// void	check_registre(std::string pass);
		bool	check_registration(Client *user);
		// Client	*get_connect_client(int fd);
		void	set_ipAddress(std::string ip);
		~Client();
};

#endif