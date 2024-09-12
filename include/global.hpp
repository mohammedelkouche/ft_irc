#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "client.hpp"
#include <iostream>

class Client;
void                        SendResponse(Client *client, std::string msg);
std::vector<std::string>    Splitter(std::string cmd, std::string delimiter);
bool                        IsClientInChannel(std::vector<Client *> ClientssHouse, int fd);
std::vector<std::string>    split(std::string commande, char delimeter);


#endif
