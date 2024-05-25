#include "../include/channels.hpp"

Channels::Channels(std::string name): name(name)
{
    bool_topic = false;
    topic = "";
}

Channels::Channels()
{
}

void print(std::vector<int> v)
{
    std::cout << "-----------------\n";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << std::endl;
    std::cout << "-----------------\n";
}

void Channels::join(int clientFd, Client *client)
{
    // print(ClientssHouse);
    // Send JOIN message to the client;
    if(std::find(ClientssHouse.begin(), ClientssHouse.end(), clientFd) == ClientssHouse.end())
    {
        std::string rpl = REPLY_JOIN(client->get_nickname(), client->get_username(), name, "localhost");
        ClientssHouse.push_back(clientFd);
        if(send(clientFd, rpl.c_str(), rpl.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
    }
    else
    {
        std::string msg = ERROR_ALREADYREGISTERED(client->get_nickname(), getChannelName());
        if (send(clientFd, msg.c_str(), msg.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
    }

}

void Channels::set_topic(std::string topic)
{
    this->topic = topic;
    bool_topic = true;
}


std::string Channels::getChannelName()
{
    return(name);
}

Channels::~Channels()
{

}

Channels::Channels(const Channels& copy) {
    name = copy.name;
    for(size_t i = 0; i < ClientssHouse.size(); i++)
        ClientssHouse[i] = copy.ClientssHouse[i];
}
