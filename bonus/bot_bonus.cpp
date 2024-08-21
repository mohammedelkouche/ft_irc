/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/21 22:03:56 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot_bonus.hpp"
#include<cstring>
#include<string>


Bot::Bot(const std::string  ip, int port) : port(port), server_ip(ip), bot_fd(-1), terminate(false)
{
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	// server_addr.sin_addr.s_addr = inet_addr(address.c_str());
	if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0)
		throw std::runtime_error("Invalid address/ Address not supported");
    
     // Ignore SIGPIPE signals
    signal(SIGPIPE, SIG_IGN);

    // Set up signal handling for termination
    signal(SIGINT, signalHandler);

}

// add test 
void Bot::setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("Failed to get socket flags");
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("Failed to set socket to non-blocking");
    }
}


void	Bot::ConnectToServer()
{
	bot_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (bot_fd < 0)
		throw std::runtime_error("Socket creation error");

    // add test 

    // setNonBlocking(bot_fd);
    
	// if (connect(bot_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) < 0))
	if (connect(bot_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		close(bot_fd);
		// throw std::runtime_error("Connection Failed");
		throw std::runtime_error("Connection failed: " + std::string(strerror(errno)));

	}
	// std::cout << "Connected to the server" << std::endl;
	std::cout << "Connected to server on port " << port << std::endl; // Use the port field here

}

std::string	Bot::ReceiveMessage()
{
	// char buffer[1024];

	// size_t bytes_received = recv(bot_fd, buffer, sizeof(buffer) - 1, 0);
	// if (bytes_received < 0)
	// 	throw std::runtime_error("Failed to receive message");
	// buffer[bytes_received] = '\0';
	// // std::cout << "Received message: " << buffer << std::endl;
	// return (std::string (buffer));
    
    
    
    // add 
    char buffer[1024];
    size_t bytes_received = recv(bot_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        if (bytes_received == 0) {
            std::cout << "Server closed connection." << std::endl;
        } else {
            std::cerr << "Receive error: " << strerror(errno) << std::endl;
        }
        terminate = true;
        std::cerr << "hhhhhhhhhh controoooool ccccccccc: " << strerror(errno) << std::endl;
        return "";
    }
    buffer[bytes_received] = '\0';
    return std::string(buffer);
}

int	Bot::ChoiceToInt(const std::string &choice)
{
	if (choice == "rock")
		return (0);
	if (choice == "paper")
		return (1);
	if (choice == "scissors")
		return (2);
	return (-1);
}

void Bot::SendMessage(const std::string &message) {
    if (send(bot_fd, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "Failed to send message " << std::endl;
    }
}

// add
void Bot::PrSendMessage(const std::string &message, const std::string &client_nick)
{
    std::string formatted_message = "PRIVMSG " + client_nick + " :" + message + "\r\n";
    if (send(bot_fd, formatted_message.c_str(), formatted_message.length(), 0) < 0)
    {
        // RemoveClient(client_nick); // Remove client if sending fails
        std::cerr << "Failed to send message to client " << client_nick << std::endl;
    }
}

// add
void Bot::signalHandler(int signal)
{
    if (signal == SIGINT) {
        // Terminate the bot safely
        std::cout << "Termination signal received. Cleaning up." << std::endl;
        exit(0); // Exit the program after cleanup
    }
}



// void Bot::RemoveClient(int client_fd) {
//     close(client_fd);
//     connected_clients.erase(client_fd);
//     std::cout << "Client " << client_fd << " disconnected and removed from the list." << std::endl;
// }


// void Bot::RemoveClient(int client_fd)
// {
//     close(client_fd);
//     client_fds.erase(std::remove(client_fds.begin(), client_fds.end(), client_fd), client_fds.end());
// }


// void	Bot::PlayGame()
// {
// 	std::srand(std::time(0));
// 	std::string choices[] = {"rock", "paper", "scissors"};
// 	while (true)
//     {
//         std::string client_message = ReceiveMessage();
//         if (client_message.size() >= 2 && client_message.substr(client_message.size() - 2) == "\r\n") 
//             client_message.erase(client_message.size() - 2);
        
//         std::istringstream iss(client_message);
    
//         // Variables to hold the parts of the message
//         std::string senderdomaine;
//         std::string command;
//         std::string receiver;
//         std::string msgContent;
        
//         iss >> senderdomaine;
//         std::string sender = senderdomaine.substr(1, senderdomaine.find('!') - 1);
//         iss >> command;
//         iss >> receiver;
//         std::getline(iss, msgContent); // Get the rest of the line


//         // Remove the leading ': ' from the message content
//         if (!msgContent.empty() && msgContent[0] == ' ' && msgContent[1] == ':') {
//             msgContent = msgContent.substr(2);
//         }

//         std::cout << "msgContent =>>" << msgContent<< "<<=" <<std::endl;
//             // Check if the command is 'privmsg'
//             if (command == "PRIVMSG")
//             {
//                 if (msgContent == "start")
//                 {
//                     PrSendMessage("Game started. Send 'rock', 'paper', or 'scissors'.", sender);
//                 }
//                 else if (msgContent == "exit")
//                 {
//                     PrSendMessage("Game ended.", sender);
//                     break;
//                 }
//                 else
//                 {
//                     int client_choice = ChoiceToInt(msgContent);
//                     if (client_choice != -1)
//                     {
//                         int bot_choice = std::rand() % 3;
//                         PrSendMessage("Bot chose " + std::string(choices[bot_choice]), sender);
                        
//                         switch (client_choice)
//                         {
//                         case 0: // client chose rock
//                             switch (bot_choice)
//                             {
//                             case 0: PrSendMessage("It's a tie", sender); break;
//                             case 1: PrSendMessage("Bot wins!", sender); break;
//                             case 2: PrSendMessage("You win!", sender); break;
//                             }
//                             break;
//                         case 1: // Client chose paper
//                             switch (bot_choice)
//                             {
//                             case 0: PrSendMessage("You win!", sender); break;
//                             case 1: PrSendMessage("It's a tie!", sender); break;
//                             case 2: PrSendMessage("Bot wins!", sender); break;
//                             }
//                             break;
//                         case 2: // Client chose scissors
//                             switch (bot_choice)
//                             {
//                             case 0: PrSendMessage("Bot wins!", sender); break;
//                             case 1: PrSendMessage("You win!", sender); break;
//                             case 2: PrSendMessage("It's a tie!", sender); break;
//                             }
//                             break;
//                         }
//                     }
//                     else
//                     {
//                         PrSendMessage("Invalid input. Send 'rock', 'paper', or 'scissors' to play, or 'exit' to quit.", sender);
//                     }
//                 }
//             }
//         }
// }


////////// add 


void Bot::PlayGame()
{
    std::srand(std::time(0));
    std::string choices[] = {"rock", "paper", "scissors"};
    
    // std::map<std::string, bool> client_in_game; // Map to track clients' game status

    while (!terminate) {
        std::string client_message = ReceiveMessage();
        if (client_message.empty()) {
            break; // Exit the loop if connection is closed or termination is requested
        }
        if (client_message.size() >= 2 && client_message.substr(client_message.size() - 2) == "\r\n") 
            client_message.erase(client_message.size() - 2);
        
        std::istringstream iss(client_message);
    
        // Variables to hold the parts of the message
        std::string senderdomaine;
        std::string command;
        std::string receiver;
        std::string msgContent;
        
        iss >> senderdomaine;
        std::string sender = senderdomaine.substr(1, senderdomaine.find('!') - 1);
        iss >> command;
        iss >> receiver;
        std::getline(iss, msgContent); // Get the rest of the line

        // Remove the leading ': ' from the message content
        if (!msgContent.empty() && msgContent[0] == ' ' && msgContent[1] == ':') {
            msgContent = msgContent.substr(2);
        }

        std::cout << "msgContent =>>" << msgContent << "<<=" << std::endl;
        
        if (client_in_game.find(sender) == client_in_game.end()) {
            client_in_game[sender] = false; 
        }
        
        if (command == "PRIVMSG") {
            if (msgContent == "start") {
                client_in_game[sender] = true;
                PrSendMessage("Game started. Send 'rock', 'paper', or 'scissors'.", sender);
            }
            else if (msgContent == "exit") {
                client_in_game[sender] = false;
                client_in_game.erase(sender);
                PrSendMessage("Game ended.", sender);
            }
            else if (client_in_game[sender]) {
                int client_choice = ChoiceToInt(msgContent);
                if (client_choice != -1) {
                    int bot_choice = std::rand() % 3;
                    PrSendMessage("Bot chose " + std::string(choices[bot_choice]), sender);

                    switch (client_choice) {
                    case 0: // Client chose rock
                        switch (bot_choice) {
                        case 0: PrSendMessage("It's a tie", sender); break;
                        case 1: PrSendMessage("Bot wins!", sender); break;
                        case 2: PrSendMessage("You win!", sender); break;
                        }
                        break;
                    case 1: // Client chose paper
                        switch (bot_choice) {
                        case 0: PrSendMessage("You win!", sender); break;
                        case 1: PrSendMessage("It's a tie!", sender); break;
                        case 2: PrSendMessage("Bot wins!", sender); break;
                        }
                        break;
                    case 2: // Client chose scissors
                        switch (bot_choice) {
                        case 0: PrSendMessage("Bot wins!", sender); break;
                        case 1: PrSendMessage("You win!", sender); break;
                        case 2: PrSendMessage("It's a tie!", sender); break;
                        }
                        break;
                    }
                } else {
                    PrSendMessage("Invalid input. Send 'rock', 'paper', or 'scissors' to play, or 'exit' to quit.", sender);
                }
            } else {
                PrSendMessage("You must send 'start' to begin the game.", sender);
            }
        }
    }
    // Cleanup();
}

bool	Bot::Authenticate()
{
	std::string nick, user, pass;
    std::cout << "Enter password: ";
    std::cin >> pass;
    std::cout << "Enter nickname: ";
    std::cin >> nick;
    std::cout << "Enter username: ";
    std::cin >> user;

    SendMessage("PASS " + pass + "\r\n");
    SendMessage("NICK " + nick + "\r\n");
    SendMessage("USER " + user + " 0 * " + user + "\r\n");

    std::string response = ReceiveMessage();
    std::cout << "Server: " << response << std::endl;

    // Assuming "001" is the successful login code
    if (response.find("001") != std::string::npos)
	{
        std::cout << "Authentication successful." << std::endl;
        return true;
    }
	else
        return false;

    // add test 
    
    //  std::string nick, user, pass;

    // struct pollfd fds[1];
    // fds[0].fd = bot_fd;
    // fds[0].events = POLLIN;

    // while (!terminate) {
    //     std::cout << "Enter password: ";
    //     std::cin >> pass;

    //     int poll_result = poll(fds, 1, 0); // Check the socket for any events with a timeout of 0 (non-blocking)
    //     if (poll_result > 0) {
    //         std::string response = ReceiveMessage();
    //         if (response.empty()) {
    //             terminate = true;
    //             break;
    //         }
    //     }

    //     std::cout << "Enter nickname: ";
    //     std::cin >> nick;

    //     poll_result = poll(fds, 1, 0);
    //     if (poll_result > 0) {
    //         std::string response = ReceiveMessage();
    //         if (response.empty()) {
    //             terminate = true;
    //             break;
    //         }
    //     }

    //     std::cout << "Enter username: ";
    //     std::cin >> user;

    //     poll_result = poll(fds, 1, 0);
    //     if (poll_result > 0) {
    //         std::string response = ReceiveMessage();
    //         if (response.empty()) {
    //             terminate = true;
    //             break;
    //         }
    //     }

    //     SendMessage("PASS " + pass + "\r\n");
    //     SendMessage("NICK " + nick + "\r\n");
    //     SendMessage("USER " + user + " 0 * " + user + "\r\n");

    //     std::string response = ReceiveMessage();
    //     std::cout << "Server: " << response << std::endl;

    //     if (terminate) {
    //         break; // Exit if terminate flag is set
    //     }

    //     // Assuming "001" is the successful login code
    //     if (response.find("001") != std::string::npos) {
    //         std::cout << "Authentication successful." << std::endl;
    //         return true;
    //     } else {
    //         std::cout << "Authentication failed. Please try again." << std::endl;
    //     }
    // }
    // return false;
}

void	Bot::Run()
{
	ConnectToServer();
	while (!terminate && !Authenticate()) 
    {
		std::cout << "Authentication failed. Please try again." << std::endl;
    }
    std::cout << "miyyyyyyyyaaaaw" << std::endl;
    if (!terminate)
	    PlayGame();
}

void Bot::Cleanup()
{
    std::cout << " test test alla h  " << std::endl;
    if (bot_fd >= 0) {
        close(bot_fd);
        bot_fd = -1;
    }
    client_in_game.clear(); // Clear the client_in_game map
}

Bot::~Bot()
{
    std::cout << " hooooooo lallalllll  " << std::endl;
    Cleanup();
}