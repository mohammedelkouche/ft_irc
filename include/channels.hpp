#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sys/socket.h>
#include"client.hpp"
#include "reply.hpp"


class Channels
{
    private:
        std::string name;
        std::vector<int> ClientssHouse;
        // std::vector<Client> ClientssHouse;
    public:
        Channels(std::string name);
        Channels();
        Channels(const Channels& copy);
        void join(Client *client);
        // bool clientExists(int clientFd);
        ~Channels();
        std::string getChannelName();
    };

#endif