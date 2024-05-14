#include "../include/channels.hpp"

Channels::Channels(std::string name): name(name)
{
}

Channels::Channels()
{

}

// bool Channels::clientExists(int clientFd)
// {
//     //search for the client fd in the vector
//     return ;
// }

void Channels::join(int clientFd, Client *client)
{
    std::string joinMessage = "JOIN " + name + "\r\n";
    // Send JOIN message to the client
    if(std::find(ClientssHouse.begin(), ClientssHouse.end(), clientFd) == ClientssHouse.end())
    {
        // std::cout<< "before push   :" << ClientssHouse[0]<< std::endl;
        ClientssHouse.push_back(clientFd);
        return;
        // std::cout<< "after push   :" << ClientssHouse[0]<< std::endl;
        if (send(clientFd, joinMessage.c_str(), joinMessage.length(), 0))
            throw std::runtime_error("Failed Send JOIN message to the client");
    }
    else
    {
        std::cout<< "HEEEEEEEEEEEEEEERE\n";
        std::string msg = ERR_ALREADYREGISTERED(client->get_nickname(), getChannelName());
        if (send(clientFd, msg.c_str(), msg.length(), 0))
            return;
        else
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