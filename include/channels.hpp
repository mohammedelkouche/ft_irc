#ifndef MY_COMMANDS_HPP
#define MY_COMMANDS_HPP

#include<iostream>
#include<string>
#include<vector>
#include"../Server/include/client.hpp"


class Channels
{
    private:
        std::string name;
        std::vector<Client> ClientssHouse;
    public:
        std::string getChannelName();
        Channels();
        ~Channels();
    };

#endif