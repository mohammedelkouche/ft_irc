#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include<iostream>
#include<string>
#include<vector>

#include "server.hpp"
#include "client.hpp"
#include "channels.hpp"

void JoinConstruction(std::vector<std::string> command, int clientFd);

#endif