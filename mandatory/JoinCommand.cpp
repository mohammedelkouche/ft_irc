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
        std::cout << " Failed Send JOIN message to the client " << std::endl;
        // throw std::runtime_error("");
}

std::string Server::buildNamReply(Channel *channel) 
{
    std::string reply;
    std::vector<Client*> clients = channel->GetClientssHouse();
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* client = *it;
        if (channel->getTheOperator() == client)
            reply += "@" + channel->getTheOperator()->get_nickname();
        else
            reply += client->get_nickname();
        
        if (it + 1 != clients.end())
            reply += " ";
    }
    return reply;
}

void Server::selfJoinReply(Client *client, Channel *channel)
{
    SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channel->getChannelName(), client->get_hostname()));
    SendResponse(client, REPLY_NAMREPLY(client->get_hostname(), buildNamReply(channel), channel->getChannelName(), client->get_nickname()));
    SendResponse(client, REPLY_ENDOFNAMES(client->get_hostname(), client->get_nickname(), channel->getChannelName()));
}



void Server::JoinConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();

    // if(cmd[0] && cmd[1] == "0")
    // {
        //if the client sends JOIN 0,
        // remove them from all channels they are currently in.
        // This would involve sending a PART message to all channels they leave.
    // }

    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1])
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return ;
    }

    std::vector<std::string> channelNames = Splitter(cmd[1], ",");
    std::vector<std::string> splittedKeys;
    bool hasKey = false;
    std::vector<std::string>::iterator keyIt;
    
    std::string key_var;

    if (cmd.size() == 3)
    {
        splittedKeys = Splitter(cmd[2], ",");
        keyIt = splittedKeys.begin();
        hasKey = true;
    }
    else if (cmd.size() == 4 && cmd[2] == ":")
    {
        splittedKeys = Splitter(cmd[3], ",");
        keyIt = splittedKeys.begin();
        hasKey = true;
    }
    // for (size_t i = 0 ; i < splittedKeys.size(); i++)
    //     std::cout << "########### Splitted key_vars ########### -> " << splittedKeys[i] << std::endl;
    for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it)
    {
        std::string channelName = *it;
        if (hasKey && keyIt != splittedKeys.end())
        {
            key_var = *keyIt;
            if (!key_var.empty() && key_var[0] == ':')
                key_var.erase(0,1);
            std::cout << "erase: [" << key_var << "]" << std::endl;
            ++keyIt;
        }
        else  
            key_var = "";
        if (channelName[0] != '#')
        {
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), channelName, client->get_nickname()));
            continue ;
        }
        else if (!channelName[1])
        {
            SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
            continue ;
        }
        std::vector<Channel*>::iterator channelIt;
        for (channelIt = channels.begin(); channelIt != channels.end(); ++channelIt)
            if ((*channelIt)->getChannelName() == channelName)
                break;

        if (channelIt == channels.end()) 
        {
            // Channel doesn't exist, create new channel and add client
            Channel* newChannel = new Channel(channelName, key_var);
            if (!newChannel->addToChannel(client, key_var))
                continue ;
            channels.push_back(newChannel);
            client->getInvitedChannels().push_back(channelName);
            ////////////////////////////
            selfJoinReply(client, newChannel);
            ///////////////////////////
            sendToChannel(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()), channelName);
            std::cout << "Channel created: " << channelName << " with client: " << client->get_nickname() << std::endl;
        }
        else
        {
            // Channel exists, add client to the channel
            if (!(*channelIt)->addToChannel(client, key_var))
                continue ;
            client->getInvitedChannels().push_back(channelName);
            // SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()));
            // SendResponse(client, REPLY_NAMREPLY(client->get_hostname(), buildNamReply(channel), channel->getChannelName(), client->get_nickname()));
            // SendResponse(client, REPLY_ENDOFNAMES(client->get_hostname(), client->get_nickname(), channelName));
            //////////////////////
            selfJoinReply(client, getChannelByName(channels, channelName));
            //////////////////////
            sendToChannel(client,REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()), channelName);
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
