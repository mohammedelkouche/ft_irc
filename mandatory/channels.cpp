#include "../include/channels.hpp"

Channel::Channel(std::string name): name(name)
{
}

Channel::Channel()
{
}

void print(std::vector<int> v)
{
    std::cout << "-----------------\n";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << std::endl;
    std::cout << "-----------------\n";
}

bool IsClientInChannel(std::vector<Client *> ClientssHouse, int fd)
{
    for(size_t i = 0; i < ClientssHouse.size(); i++)
        if(ClientssHouse[i]->get_fd() == fd)
            return true;
    return false;
}

void Channel::addToChannel(Client *client)
{
    // print(ClientssHouse);
    // Send JOIN message to the client;
    if(IsClientInChannel(ClientssHouse, client->get_fd()) == false)
    {
        // clients still undefined in join reply replaced just with a nickname
        std::string rpl = REPLY_JOIN(client->get_nickname(), client->get_username(), name, client->get_hostname());
        ClientssHouse.push_back(client);
        std::cout<< rpl;
        std::cout << REPLY_NAMREPLY(client->get_hostname(), client->get_nickname(), getChannelName(), client->get_nickname()) \
        << REPLY_ENDOFNAMES(client->get_hostname(), client->get_nickname(), getChannelName()) << std::endl;
        SendResponse(client, rpl);
    }
    else
        SendResponse(client, ERROR_ALREADYREGISTERED(client->get_nickname(), getChannelName()));

}

void Channel::setChannelName(std::string name)
{
    this->name = name;
}

std::vector<Client *> Channel::GetClientssHouse()
{
    return(this->ClientssHouse);
}

std::string Channel::getChannelName()
{
    return(name);
}

Channel::~Channel()
{

}

Channel::Channel(const Channel& copy) {
    name = copy.name;
    for(size_t i = 0; i < ClientssHouse.size(); i++)
        ClientssHouse[i] = copy.ClientssHouse[i];
}
