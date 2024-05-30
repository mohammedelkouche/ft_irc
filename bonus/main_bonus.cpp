/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:52:46 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/26 17:11:24 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bot_bonus.hpp"

void	CheckArg(char **argv)
{
	int port;
	std::string ip_address(argv[1]);
	std::string portstr(argv[2]);
	size_t portPos = portstr.find_first_not_of("0123456789");
	if (portPos != std::string::npos) {
		throw std::invalid_argument("Error: Invalid characters in port");
	}
	std::stringstream portstream(portstr);
	portstream >> port;
	// if (portstream.fail()) {
	//     throw std::invalid_argument("Error: Failed to convert port to integer");
	// }
	if (port < 1024 || port > 65535) {
		throw std::out_of_range("Error: Invalid port number");
	}
	if (ip_address != "localhost" && ip_address != "127.0.0.1")
		throw std::invalid_argument("Error: Invalid ip_address");
	
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "write executable file  <port> <password>" << std::endl;
		return 1;
	}
	try
	{
		CheckArg(argv);
		Bot bot(argv[1], std::atoi(argv[2]));
		bot.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}