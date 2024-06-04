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


void Channel::join(Client *client)
{
    // print(ClientssHouse);
    // Send JOIN message to the client;
    if(std::find(ClientssHouse.begin(), ClientssHouse.end(), client->get_fd()) == ClientssHouse.end())
    {
        // clients still undefined in join reply replaced just with a nickname
        std::string rpl = REPLY_JOIN(client->get_nickname(), client->get_username(), name, client->get_hostname());
        ClientssHouse.push_back(client->get_fd());
        std::cout<< rpl;
        std::cout << REPLY_NAMREPLY(client->get_hostname(), client->get_nickname(), getChannelName(), client->get_nickname()) \
        << REPLY_ENDOFNAMES(client->get_hostname(), client->get_nickname(), getChannelName()) << std::endl;
        SendResponse(client, rpl);
    }
    else
        SendResponse(client, ERROR_ALREADYREGISTERED(client->get_nickname(), getChannelName()));

}

std::vector<int> Channel::GetClientssHouse()
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
