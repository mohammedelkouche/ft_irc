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

void Channels::join(Client *client)
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
        if(send(client->get_fd(), rpl.c_str(), rpl.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
    }
    else
    {
        std::string msg = ERROR_ALREADYREGISTERED(client->get_nickname(), getChannelName());
        if (send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
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
