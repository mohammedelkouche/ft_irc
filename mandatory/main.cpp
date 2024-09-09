/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:08:30 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/06 01:45:25 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/server.hpp"


void check_arg(char **argv) {
	std::string portstr(argv[1]);
	size_t portPos = portstr.find_first_not_of("0123456789");
	if (portPos != std::string::npos) {
		throw std::invalid_argument("Error: Invalid characters in port");
	}
	int port;
	std::stringstream portstream(portstr);
	portstream >> port;
	if (port < 1024 || port > 65535) {
		throw std::out_of_range("Error: Invalid port number");
	}
	if (std::strlen(argv[2]) == 0) {
		throw std::invalid_argument("Error: Empty password");
	}
}

void printIntro() 
{
    std::string reset = "\033[0m";
	std::string green = "\033[32m";
	std::string blue = "\033[34m";

	std::cout << green;
    std::cout << " _   _        __        __   _                            __  __       _    _ _      _     _   " << std::endl;
    std::cout << "| \\ | | ___   \\ \\      / /__| | ___ ___  _ __ ___   ___  |  \\/  | __ _| |_ (_|_) ___| |__ (_)" << std::endl;
    std::cout << "|  \\| |/ _ \\   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\\/| |/ _` | __|| | |/ __| '_ \\| |" << std::endl;
    std::cout << "| |\\  | (_) |   \\ V  V /  __/ | (_| (_) | | | | | |  __/ | |  | | (_| | |_ | | | (__| | | | |" << std::endl;
    std::cout << "|_| \\_|\\___/     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| |_|  |_|\\__,_|\\__|/ |_|\\___|_| |_|_|" << std::endl;
    std::cout << "                                                                         |__/               "<<std::endl;
    std::cout << reset;
    std::cout << blue  << " Hahaha Just Kidding Welcome To the best IRC server made by RIJAL ❤️"  << reset << std::endl;
}

int main(int argc, char **argv) {
	try 
	{
		Server irc;
		
		if (argc != 3)
		{
			std::cout << "write: executable file  <port> <password>" << std::endl;
			return 1;
		}
		check_arg(argv);
		printIntro();
		irc.initializeServer(std::atoi(argv[1]), argv[2]);
	}
	catch (const std::invalid_argument& e) 
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const char *error_message)
	{
		std::cerr << error_message << std::endl;
		return 1;
	}
	return 0;
}
