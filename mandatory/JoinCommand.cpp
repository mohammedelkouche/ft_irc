#include "../include/server.hpp"

std::vector<std::string> Splitter(std::string cmd, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;
    while ((pos = cmd.find(delimiter)) != std::string::npos)
    {
        token = cmd.substr(0, pos);
        result.push_back(token);
        cmd.erase(0, pos + delimiter.length());
    }
    result.push_back(cmd);
    return result;
}

bool Server::channeDoesntlExists(std::vector<Channel*> haystack, std::string needle)
{
    for (size_t i = 0; i < haystack.size(); i++)
        if (haystack[i]->getChannelName() == needle)
            return false;
    return true;
}

void SendResponse(Client *client, std::string msg)
{
    if (send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
        std::cerr << "send() faild" << std::endl;
        // throw std::runtime_error("Failed Send JOIN message to the client"); 
}

void Server::JoinConstruction(Client *client) 
{
    std::vector<std::string> cmd = client->get_commande();

    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1]) 
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return ;
    }

    std::vector<std::string> channelNames = Splitter(cmd[1], ",");
    for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it)
    {
        std::string channelName = *it;
        if (channelName[0] != '#')
        {
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), channelName, client->get_nickname()));
            continue ;
        }
        std::vector<Channel*>::iterator channelIt;
        for (channelIt = channels.begin(); channelIt != channels.end(); ++channelIt)
            if ((*channelIt)->getChannelName() == channelName)
                break;

        if (channelIt == channels.end()) 
        {
            // Channel doesn't exist, create new channel and add client
            Channel* newChannel = new Channel(channelName);
            if (!newChannel->addToChannel(client))
                continue ;
            channels.push_back(newChannel);
            client->getInvitedChannels().push_back(channelName);
            SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()));
            std::cout << "Channel created: " << channelName << " with client: " << client->get_nickname() << std::endl;
        }
        else
        {
            // Channel exists, add client to the channel
            if (!(*channelIt)->addToChannel(client))
                continue ;
            client->getInvitedChannels().push_back(channelName);
            SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()));
            std::cout << "Client " << client->get_nickname() << " joined existing channel: " << channelName << std::endl;
        }
    }
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        std::cout << "Channel: " << (*it)->getChannelName() << std::endl;
        std::vector<Client*> clientsHouse = (*it)->GetClientssHouse();
        if (clientsHouse.empty())
        {
            std::cout << "No clients in channel: " << (*it)->getChannelName() << std::endl;
            continue;
        }
        for (std::vector<Client*>::iterator clientIt = clientsHouse.begin(); clientIt != clientsHouse.end(); ++clientIt)
        {
            std::cout << "Client fd: " << (*clientIt)->get_fd()
                      << " nickname: " << (*clientIt)->get_nickname()
                      << " operator status: " << (*clientIt)->getIsOperatorStatus() << std::endl;
        }
    }
}