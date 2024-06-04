#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "client.hpp"
#include <iostream>

class Client;
void SendResponse(Client *client, std::string msg);
std::vector<std::string> Splitter(std::vector<std::string> cmd, std::string delimiter);


#endif
