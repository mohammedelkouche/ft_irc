#ifndef Channel_HPP
#define Channel_HPP

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sys/socket.h>
#include"client.hpp"
#include "global.hpp"
#include "reply.hpp"

class Client;
class Channel
{
    private:
        std::string name;
        std::vector<Client *> ClientssHouse;
    public:
        Channel(std::string name);
        Channel();
        Channel(const Channel& copy);
        void addToChannel(Client *client);
        // bool clientExists(int clientFd);
        ~Channel();
        void setChannelName(std::string name);
        std::string getChannelName();
        std::vector<Client *> GetClientssHouse();
    };
#endif