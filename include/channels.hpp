#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sys/socket.h>
#include"client.hpp"
#include "reply.hpp"
#include "topic.hpp"


class Channels
{
    private:
        std::string         name;
        std::vector<int>    ClientssHouse;
        std::string         topic;
        bool                bool_topic;
        // std::vector<Client> ClientssHouse;
    public:
        Channels(std::string name);
        Channels();
        Channels(const Channels& copy);
        void join(int clientFd, Client *client);
        void set_topic(std::string topic);
        std::string get_topic();
        // bool clientExists(int clientFd);
        ~Channels();
        std::string getChannelName();
    };

#endif