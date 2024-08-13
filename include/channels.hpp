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
        std::vector<Client *> Operators;
    public:
        Channel();
        Channel(std::string name);
        Channel(const Channel& copy);
        ~Channel();
        bool addToChannel(Client *client);
        void removeFromChannel(Client *client);
        // bool clientExists(int clientFd);
        void setChannelName(std::string name);
        std::string getChannelName();
        Client* getTheOperator();
        std::vector<Client *> GetClientssHouse();
        std::vector<Client *> GetTheOperators();
    };
#endif