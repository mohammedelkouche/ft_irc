#include "../include/channels.hpp"

Channel::Channel(std::string name, std::string key): name(name), key(key)
{
    init_modes();
    setTheChannelTimeCreated();
    
}

Channel::Channel()
{
    this->key = "";
    init_modes();
}

void Channel::setTheChannelTimeCreated()
{
    time_t present_time;
    present_time = time(NULL);
    std::ostringstream oss;
    oss << present_time;
    std::string time_now = oss.str();
    this->channelTime = time_now;
}

std::string Channel::getTheChannelTimeCreated()
{
    return channelTime;
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

bool Channel::addToChannel(Client *client, std::string key)
{
    if (IsClientInChannel(ClientssHouse, client->get_fd()))
    {
        SendResponse(client, ERROR_USERONCHANNEL(client->get_hostname(), getChannelName(), client->get_nickname()));
        return false;
    }
    if(get_k() == true)
    {
        if (!this->key.empty() && getChannelKey() != key)
        {
            SendResponse(client, ERROR_BADCHANNELKEY(client->get_nickname(), client->get_hostname(), getChannelName()));
            return false;
        }
    }
    bool shouldSetOperator = ClientssHouse.empty();
    client->setOperatorStatus(shouldSetOperator);
    Client *newClient = new Client(*client);
    ClientssHouse.push_back(newClient);
    return true;
}

Client* NO_OPERATOR = NULL;

void Channel::removeFromChannel(Client *client)
{
    Client *Coperator = getTheOperator();

    if(IsClientInChannel(ClientssHouse, client->get_fd()))
    {
        for(size_t i = 0; i < ClientssHouse.size(); i++)
            if(ClientssHouse[i]->get_fd() == client->get_fd())
            {
                delete (ClientssHouse[i]);
                ClientssHouse.erase(ClientssHouse.begin() + i);
                break ;
            }
    }
    if (Coperator == NO_OPERATOR)
        return;
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

std::string Channel::getChannelKey()
{
    return key;
}

size_t Channel::getChannelLimitNum()
{
    return limit;
}

Channel::~Channel()
{
}

Channel::Channel(const Channel& copy) 
{
    init_modes();
    name = copy.name;
    key = copy.key;
    for(size_t i = 0; i < ClientssHouse.size(); i++)
        ClientssHouse[i] = copy.ClientssHouse[i];
}
