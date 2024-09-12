/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:52:46 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/09 02:42:46 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot_bonus.hpp"

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
	if (port < 1024 || port > 65535) {
		throw std::out_of_range("Error: Invalid port number");
	}
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "write < executable file > < 127.0.0.1 >  <port>  <pass>" << std::endl;
		return 1;
	}
	try
	{
		CheckArg(argv);
		Bot bot(argv[1], std::atoi(argv[2]), argv[3]);
		bot.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}