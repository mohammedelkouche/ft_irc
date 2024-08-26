/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/26 22:05:23 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot_bonus.hpp"
#include<cstring>
#include<string>


Bot::Bot(const std::string &ip, int port, const std::string &password) : port(port), server_ip(ip), bot_fd(-1), password(password) ,terminate(false)
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
    
    std::srand(std::time(0)); // Initialize random number generator

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
    
	if (connect(bot_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		close(bot_fd);
		throw std::runtime_error("Connection failed: " + std::string(strerror(errno)));
	}
	std::cout << "Connected to server on port " << port << std::endl;

}

std::string	Bot::ReceiveMessage()
{
    char buffer[1024];
    ssize_t bytes_received = recv(bot_fd, buffer, sizeof(buffer) - 1, 0);
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
    std::cout  << "choice -> <<"  <<  choice << ">>"<< std::endl;
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

// old
void Bot::PrSendMessage(const std::string &message, const std::string &client_nick)
{
    std::string formatted_message = "PRIVMSG " + client_nick + " :" + message + "\r\n";
    
    if (send(bot_fd, formatted_message.c_str(), formatted_message.length(), 0) < 0)
    {
        // RemoveClient(client_nick); // Remove client if sending fails
        std::cerr << "Failed to send message to client " << client_nick << std::endl;
    }
}

void Bot::signalHandler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Termination signal received. Cleaning up." << std::endl;
        exit(0);
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


void Bot::PlayRoshambo(const std::string &sender)
{
    std::string choices[] = {"rock", "paper", "scissors"};
    PrSendMessage("Send 'rock', 'paper', or 'scissors' to play.", sender);
    std::string client_message = ReceiveMessage();
    if (client_message.size() >= 2 && client_message.substr(client_message.size() - 2) == "\r\n")
        client_message.erase(client_message.size() - 2);
    size_t colonPos = client_message.find_last_of(':');

    // If ':' is found, extract the substring after it
    std::string content;
    if (colonPos != std::string::npos)
        content = client_message.substr(colonPos + 1); // Extract everything after the colon
    
    content.erase(std::remove(content.begin(), content.end(), ' '), content.end());
    int client_choice = ChoiceToInt(content);
    if (client_choice != -1)
    {
        int bot_choice = std::rand() % 3;
        PrSendMessage("Bot chose " + std::string(choices[bot_choice]), sender);
        switch (client_choice)
        {
            case 0:
                switch (bot_choice)
                {
                    case 0: PrSendMessage("It's a tie!", sender); break;
                    case 1: PrSendMessage("Bot wins!", sender); break;
                    case 2: PrSendMessage("You win!", sender); break;
                }
                break;
            case 1:
                switch (bot_choice)
                {
                    case 0: PrSendMessage("You win!", sender); break;
                    case 1: PrSendMessage("It's a tie!", sender); break;
                    case 2: PrSendMessage("Bot wins!", sender); break;
                }
                break;
            case 2:
                switch (bot_choice)
                {
                    case 0: PrSendMessage("Bot wins!", sender); break;
                    case 1: PrSendMessage("You win!", sender); break;
                    case 2: PrSendMessage("It's a tie!", sender); break;
                }
                break;
        }
    }
    else
        PrSendMessage("Invalid input. Send 'rock', 'paper', or 'scissors' to play.", sender);
}

void Bot::PlayNwetat(const std::string &sender)
{
    std::string nwetat_arr[] = 
    {
        "galk wlah wmaknti zwen lasybty irc 7da twin",
        "gals gals rebbi l flals w weklhom lkhobz yabes w t3alem srabss",
        "tahya khassa l ay 3abdia 7la mn l hendia w b7alha b7al chehdya w machi beldya",
        "galk li zin zin wakha i3om mn tnin l tnin , wli khayb khayb wakha i3om blma tayb",
        "tahya khassa l khouya aymen rak 7ader nadr w dareb ndader w katchtef lia 3el lkyader tchanchit w chi maychit",
        "galk aymane douzi 3ando l insta bach takli l passta , w galk oussama douzi 3ando l facebook atl9ayh dayr f profil rwayda bla slouk ",
        "galk sel3a slou3 w mohammed mol l bot ga3ma mekhlou3 , tahyati l khouya mohammed lkouk wl kheyzzo me7kouk"
    };

    std::vector<std::string> sentences(nwetat_arr, nwetat_arr + sizeof(nwetat_arr) / sizeof(nwetat_arr[0]));
    int random_index = std::rand() % sentences.size();
    PrSendMessage(sentences[random_index], sender);
}

void Bot::PlayGame()
{
    while (!terminate) {
        std::string client_message = ReceiveMessage();
        if (client_message.empty()) // like Server closed connection
            break;

        if (client_message.size() >= 2 && client_message.substr(client_message.size() - 2) == "\r\n") 
            client_message.erase(client_message.size() - 2);
        
        std::istringstream iss(client_message);
        std::string senderdomaine;
        std::string command;
        std::string receiver;
        std::string msgContent;

        iss >> senderdomaine;
        iss >> command;
        iss >> receiver;
        std::getline(iss, msgContent);

        if (!msgContent.empty() && msgContent[0] == ' ' && msgContent[1] == ':') {
            msgContent = msgContent.substr(2);
        }

        if (command == "PRIVMSG")
        {
            std::string sender = senderdomaine.substr(1, senderdomaine.find('!') - 1);
            if (msgContent == "start")
            {
                PrSendMessage("Choose a game: 'Roshambo(rock paper scissors)' or 'Nwetat'. Type 'exit' to quit.", sender);
                client_in_game[sender] = true;
            } 
            else if (msgContent == "Roshambo" && client_in_game[sender])
                PlayRoshambo(sender);
            else if (msgContent == "Nwetat" && client_in_game[sender])
                PlayNwetat(sender);
            else if (msgContent == "exit" && client_in_game[sender])
            {
                PrSendMessage("You have exited the game. Type 'start' to play again.", sender);
                client_in_game[sender] = false;
            }
            else if (client_in_game[sender])
                PrSendMessage("Invalid input. Choose 'Roshambo', 'Nwetat', or 'exit'.", sender);
            else if (!client_in_game[sender])
                PrSendMessage("You must send 'start' to begin the game.", sender);
        }
    }
    // Cleanup();
}

bool	Bot::Authenticate()
{
	std::string nick, user;
    nick = "bot";
    user = "ahmed";

    SendMessage("PASS " + password + "\r\n");
    SendMessage("NICK " + nick + "\r\n");
    SendMessage("USER " + user + " 0 * " + user + "\r\n");

    std::string response = ReceiveMessage();
    std::cout << "Server: " << response << std::endl;

    if (response.find("001") != std::string::npos)
	{
        std::cout << "Authentication successful." << std::endl;
        return true;
    }
	else
        return false;
}

void	Bot::Run()
{
	ConnectToServer();
    if (Authenticate())
	    PlayGame();
    // Cleanup();
}

void Bot::Cleanup()
{
    std::cout << " test test alla h  " << std::endl;
    if (bot_fd >= 0) {
        close(bot_fd);
        bot_fd = -1;
    }
    client_in_game.clear();
}


Bot::~Bot()
{
    std::cout << " hooooooo lallalllll  " << std::endl;
    Cleanup();
}