#include "../include/channels.hpp"

Channels::Channels(std::string name): name(name)
{
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
    std::string joinMessage = "JOIN " + name + "\r\n";
    // Send JOIN message to the client;
    if(std::find(ClientssHouse.begin(), ClientssHouse.end(), clientFd) == ClientssHouse.end())
    {
        // std::cout << "ana ldakhel client mkainch" << std::endl;
        ClientssHouse.push_back(clientFd);
        if (send(clientFd, joinMessage.c_str(), joinMessage.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
        std::string rpl = RPL_JOIN();
        
    }
    else
    {
        std::string msg = ERR_ALREADYREGISTERED(client->get_nickname(), getChannelName());
        if (send(clientFd, msg.c_str(), msg.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
    }

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