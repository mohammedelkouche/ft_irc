/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:04:27 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/09/08 20:48:54 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot_bonus.hpp"
#include<cstring>
#include<string>


Bot::Bot(const std::string &ip, int port, const std::string &password) : port(port), server_ip(ip), bot_fd(-1), password(password) ,terminate(false)
{
    if (server_ip == "LOCALHOST")
    {
        for (std::size_t i = 0; i < server_ip.length(); ++i)
            server_ip[i] = std::tolower(server_ip[i]);
    }
    if (server_ip == "localhost")        
        server_ip = "127.0.0.1";

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0)
		throw std::runtime_error("Invalid address/ Address not supported");
    
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, signalHandler);
    
    std::srand(std::time(0)); // Initialize random number generator

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
    if (bytes_received <= 0)
    {
        if (bytes_received == 0)
            std::cout << "Server closed connection." << std::endl;
        else
            std::cerr << "Receive error: " << strerror(errno) << std::endl;
        terminate = true;
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
    if (send(bot_fd, message.c_str(), message.length(), 0) < 0)
        std::cerr << "Failed to send message " << std::endl;
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

void Bot::PlayRoshambo(const std::string &sender, const std::string &content)
{
    std::string choices[] = {"rock", "paper", "scissors"};
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

        PrSendMessage("Send 'rock', 'paper', or 'scissors' to play again, or 'exit' to quit.", sender);
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
        "galk sel3a slou3 w mohammed mol l bot ga3ma mekhlou3 , tahyati l khouya mohammed lkouk wl kheyzzo me7kouk",
        "galk l3alam kooollo wla khdam libror, li mikiddich l bizza kila77ag lhedra",
        "[1]    44471 segmentation fault  ./ircserv 8080 x ------{ CHOUF F SMA 3AWTANI CHOUF F SMA HHHHHHH }-------"
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

        if (!msgContent.empty() && msgContent[0] == ' ' && msgContent[1] == ':')
            msgContent = msgContent.substr(2);
        
        msgContent.erase(std::remove(msgContent.begin(), msgContent.end(), ' '), msgContent.end());
        
        if (command == "PRIVMSG")
        {
            std::string sender = senderdomaine.substr(1, senderdomaine.find('!') - 1);
            if (msgContent == "start")
            {
                PrSendMessage("Choose a game: 'Roshambo(rock paper scissors)' or 'Dolly'. Type 'exit' to quit.", sender);
                client_in_game[sender] = true;
                current_game[sender] = "";  // Initialize to no game selected
            }
            else if (msgContent == "Roshambo" && client_in_game[sender])
            {
                PrSendMessage("You chose Roshambo! Send 'rock', 'paper', or 'scissors' to play.", sender);
                current_game[sender] = "Roshambo";
            }
            else if (msgContent == "Dolly" && client_in_game[sender])
            {
                PrSendMessage("You chose Dolly!", sender);
                current_game[sender] = "Dolly";
                PlayNwetat(sender);
            }
            else if (msgContent == "exit" && client_in_game[sender])
            {
                PrSendMessage("You have exited the game. Type 'start' to play again.", sender);
                client_in_game[sender] = false;
                current_game[sender] = "";
            }
            else if (client_in_game[sender])
            {
                if (current_game[sender] == "Roshambo")
                    PlayRoshambo(sender, msgContent);
                else if (current_game[sender] == "Dolly" && msgContent == "Dolly")
                    PlayNwetat(sender);
                else
                    PrSendMessage("Invalid input. Choose 'Roshambo', 'Dolly', or 'exit'.", sender);
            }
            else if (!client_in_game[sender])
                PrSendMessage("You must send 'start' to begin the game.", sender);
        }
    }
}

bool	Bot::Authenticate()
{
	std::string nick, user;
    nick = "bot";
    user = "mohammed";

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
}

void Bot::Cleanup()
{
    if (bot_fd >= 0) {
        close(bot_fd);
        bot_fd = -1;
    }
    client_in_game.clear();
}


Bot::~Bot()
{
    Cleanup();
}