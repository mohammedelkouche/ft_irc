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

Client* Channel::getTheOperator()
{
    for(size_t i = 0; i < GetClientssHouse().size(); i++)
        if(GetClientssHouse()[i]->getIsOperatorStatus())
            return (GetClientssHouse()[i]);
    return NULL;
}

bool Channel::addToChannel(Client *client)
{
    std::cout << "Attempting to add client: " << client->get_nickname() << std::endl;

    if (IsClientInChannel(ClientssHouse, client->get_fd()))
    {
        SendResponse(client, ERROR_USERONCHANNEL(client->get_hostname(), getChannelName(), client->get_nickname()));
        return false;
    }
    // Determine if the client should be an operator before adding
    bool shouldSetOperator = ClientssHouse.empty();
    std::cout << "Channel is empty before adding client: " << shouldSetOperator << std::endl;
    // Set operator status
    client->setOperatorStatus(shouldSetOperator);
    Client *newClient = new Client(*client);  // Create a new Client object on the heap
    // Add client to the channel
    ClientssHouse.push_back(newClient);;
    std::cout << "Client " << newClient->get_nickname() << " added to the channel with operator status: " << newClient->getIsOperatorStatus() << std::endl;
    return true;
}

Client* NO_OPERATOR = NULL;

void Channel::removeFromChannel(Client *client)
{
    Client *Coperator = getTheOperator();
    // if (Coperator == NO_OPERATOR)
    // {
    //     std::cout << "No Operator in the channel! " << std::endl;
    //     return;
    // }
    if(IsClientInChannel(ClientssHouse, client->get_fd()))
    {
        for(size_t i = 0; i < ClientssHouse.size(); i++)
            //it s okay if the operator kicked himself (no one will be the operator in that chanel)
            if(ClientssHouse[i]->get_fd() == client->get_fd())
            {
                ClientssHouse.erase(ClientssHouse.begin() + i);
                break ;
            }
    }
    else
        SendResponse(Coperator, ERROR_NOTONCHANNEL(client->get_nickname(), getChannelName()));
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

// std::string Channel::getHasKey()
// {
//     return hasKey;
// }

// std::string Channel::getKey()
// {
//     return key;
// }

// void Channel::setKey(std::string key)
// {
//     this->key = key;
// }


Channel::~Channel()
{
}

Channel::Channel(const Channel& copy) 
{
    name = copy.name;
    for(size_t i = 0; i < ClientssHouse.size(); i++)
        ClientssHouse[i] = copy.ClientssHouse[i];
}
