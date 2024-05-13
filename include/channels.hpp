#ifndef MY_COMMANDS_HPP
#define MY_COMMANDS_HPP

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sys/socket.h>
#include"client.hpp"


class Channels
{
    private:
        std::string name;
        std::vector<int> ClientssHouse;
    public:
        Channels(std::string name);
        Channels();
        void join(int clientFd);
        ~Channels();
        std::string getChannelName();
    };

#endif