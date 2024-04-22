/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:04:57 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/22 15:05:02 by mel-kouc         ###   ########.fr       */
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
    // if (portstream.fail()) {
    //     throw std::invalid_argument("Error: Failed to convert port to integer");
    // }
    if (port < 1024 || port > 65535) {
        throw std::out_of_range("Error: Invalid port number");
    }
        if (std::strlen(argv[2]) == 0) {
        throw std::invalid_argument("Error: Empty password");
    }
}

int main(int argc, char **argv) {
    try 
	{
		Server irc;
        if (argc != 3) {
            std::cout << "write: executable file  <port> <password>" << std::endl;
            return 1;
        }
        check_arg(argv);
		irc.config_server(std::atoi(argv[1]), argv[2]);
        // std::cout << "Arguments are valid." << std::endl;
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
	catch (...) 
	{
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    return 0;
}

//---------------------------------------------------

// int	check_arg(char **argv)
// {
// 	int port;
// 	std::string str(argv[1]);
// 	size_t portstr = str.find_first_not_of("0123456789");
// 	if (portstr != std::string::npos)
// 	{
// 		std::cout << "error in the port" << std::endl;
// 		return(1);
// 	}
// 	std::stringstream my_stream(str);
// 	my_stream >> port;
// 	if (port < 1024 || port > 65535)
// 	{
// 		std::cout << "error : invalide port number" << std::endl;
// 		return(1);
// 	}
// 	return (0);
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 3)
// 	{
// 		std::cout << "write: executable file, <port> ,<password>" << std::endl;
// 		return (1);
// 	}
// 	check_arg(argv);
// 	// creat socket
// 	// int serversocket = socket(AF_INET, SOCK_STREAM, 0);
// 	// if (serversocket == -1)
// 	// {
// 	// 	std::cout << "Error could not creat socket \n";
// 	// 	// std::cerr << "Error could not creat socket \n";
// 	// 	return (1);
// 	// }
// 	// // bind the socket to an IP addres and port
// 	// // sockaddr_in serverAddress;
// 	// struct sockaddr_in serverAddress;
// 	return (0);
// }