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

Client NO_OPERATOR;

Client& Channel::getTheOperator()
{
    for(size_t i = 0; i < GetClientssHouse().size(); i++)
        if(GetClientssHouse()[i]->getIsOperatorStatus())
            return (*GetClientssHouse()[i]);
    return NO_OPERATOR;
}

void Channel::addToChannel(Client *client)
{
    if (!IsClientInChannel(ClientssHouse, client->get_fd()))
    {
        std::string rpl = REPLY_JOIN(client->get_nickname(), client->get_username(), name, client->get_hostname());
        // Determine if the client should be an operator
        bool shouldSetOperator = GetClientssHouse().empty(); // Set as operator if channel is empty
        if (shouldSetOperator)
            client->setOperatorStatus(true);  // Set operator status for the client
        ClientssHouse.push_back(client);
        std::cout<< rpl;
        std::cout << REPLY_NAMREPLY(client->get_hostname(), client->get_nickname(), getChannelName(), client->get_nickname()) \
        << REPLY_ENDOFNAMES(client->get_hostname(), client->get_nickname(), getChannelName()) << std::endl;
        // Output reply messages to client
    }
    else
    {
        SendResponse(client, ERROR_ALREADYREGISTERED(client->get_nickname(), getChannelName()));
    }
}

void Channel::removeFromChannel(Client *client, std::string comment)
{
    Client& Coperator = getTheOperator();
    if (&Coperator == &NO_OPERATOR)
    {
        std::cout << "No operator in the channel" << std::endl;
        return;
    }
    if(IsClientInChannel(ClientssHouse, client->get_fd()))
    {
        std::string rpl = REPLY_KICK(Coperator.get_nickname(), Coperator.get_username(),\
        Coperator.get_hostname(), getChannelName(), client->get_nickname(), comment);
        ClientssHouse.erase(std::remove(ClientssHouse.begin(), ClientssHouse.end(), client), ClientssHouse.end());
        // delete client;
        std::cout << rpl;
    }
    else
        SendResponse(client, ERROR_NOTONCHANNEL(client->get_nickname(), getChannelName()));
}

void Channel::setChannelName(std::string name)
{
    this->name = name;
}

std::vector<Client *> Channel::GetClientssHouse()
{
    return (this->ClientssHouse);
}

std::string Channel::getChannelName()
{
    return (name);
}

Channel::~Channel()
{

}

Channel::Channel(const Channel& copy) {
    name = copy.name;
    for(size_t i = 0; i < ClientssHouse.size(); i++)
        ClientssHouse[i] = copy.ClientssHouse[i];
}
