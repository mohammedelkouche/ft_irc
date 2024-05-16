/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:11:32 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/15 20:46:57 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <vector>


class   Client
{
	private :
		int	fd;
		std::string ipaddress;
		std::vector<std::string> commande;
		std::string nickname;
		std::string username;
		bool registred;
	public :
		Client();
		Client(const Client& copy);
		void	set_fd(int fd_client);
		void	set_commande(std::vector <std::string> &cmd);
		void	set_nickname(std::string nick);
		void	set_username(std::string user);
		bool	is_enregistred();
		std::vector<std::string>	get_commande();
		int		get_fd();
		std::string		get_nickname();
		std::string		get_username();
		// Client	*get_connect_client(int fd);
		void	set_ipAddress(std::string ip);
		~Client();
};

#endif