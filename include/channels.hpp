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
        std::string           topic;
        bool                  bool_topic;
        std::string           topic_setter;
        std::string           channelKey;
    public:
        Channel();
        Channel(std::string name, std::string key);
        Channel(const Channel& copy);
        ~Channel();
        bool                    addToChannel(Client *client, std::string key);
        void                    removeFromChannel(Client *client);
        // bool clientExists(int clientFd);
        void                    setChannelName(std::string name);
        std::string             getChannelName();
        Client*                 getTheOperator();
        std::vector<Client *>   GetClientssHouse();
        std::vector<Client *>   GetTheOperators();
        void                    set_topic(std::string topic);
        std::string             get_topic();
        void	                set_topic_setter(std::string topicsetter);
        std::string             get_topic_setter();
        std::string             getChannelKey();
    };
#endif
