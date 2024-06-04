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
        std::vector<int> ClientssHouse;
    public:
        Channel(std::string name);
        Channel();
        Channel(const Channel& copy);
        void join(Client *client);
        // bool clientExists(int clientFd);
        ~Channel();
        std::string getChannelName();
        std::vector<int> GetClientssHouse();
    };

#endif