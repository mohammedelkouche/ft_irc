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
}

std::string Server::buildNamReply(Channel *channel) 
{
    std::string reply;
    std::vector<Client*> clients = channel->GetClientssHouse();
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* client = *it;
        if(client->getIsOperatorStatus()) 
        {
            if (reply.empty())
                reply += "@" + client->get_nickname();
            else
                reply += " @" + client->get_nickname();
        }
        else
        {
            if (reply.empty())
                reply += client->get_nickname();
            else
                reply += " " + client->get_nickname();
        }
    }
    return reply;
}

void Server::selfJoinReply(Client *client, Channel *channel)
{
    SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channel->getChannelName(), client->get_hostname()));
    sendToClient(client->get_fd(), REPLY_CHANNELMODES(client->get_hostname(), channel->getChannelName(), client->get_nickname(), channel->get_channel_mode()));
    SendResponse(client, REPLY_NAMREPLY(client->get_hostname(), buildNamReply(channel), channel->getChannelName(), client->get_nickname()));
    SendResponse(client, REPLY_ENDOFNAMES(client->get_hostname(), client->get_nickname(), channel->getChannelName()));
}

void Server::joinZeroo(Client *client)
{
    bool flag = false;
    std::string channelLeft;
    for(std::vector<Channel *>::iterator iterate = channels.begin(); iterate != channels.end(); ++iterate)
    {
        for(size_t i = 0; i < (*iterate)->GetClientssHouse().size(); i++)
        {
            if((*iterate)->GetClientssHouse()[i]->get_fd() == client->get_fd())
            {
                (*iterate)->removeFromChannel((*iterate)->GetClientssHouse()[i]);
                channelLeft = (*iterate)->getChannelName();
                flag = true;
                SendResponse(client, PART_REPLY(client->get_nickname(), client->get_hostname(), client->get_username(), (*iterate)->getChannelName()));
                break ;
            }
        }
        if ((*iterate)->GetClientssHouse().size() == 0)
        {
            deleteTheChannelWhenNoUserInIt(*iterate);
            iterate--;
        }
        if (flag)
        {
            sendToChannel(client, PART_REPLY(client->get_nickname(), client->get_hostname(), client->get_username(), channelLeft), channelLeft);
            flag = false;
        }
    }
}

void Server::JoinConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();

    std::stringstream ss(cmd[1]);
    std::string zero ;
    ss >> zero; 
    if (zero == "0")
    {
        joinZeroo(client);
        return ;
    }
    else if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1])
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return ;
    }

    std::vector<std::string> channelNames = Splitter(cmd[1], ",");
    std::vector<std::string> splittedKeys;
    std::vector<std::string> initialize;
    std::vector<std::string>::iterator keyIt = initialize.begin();
    std::string key_var;
    bool hasKey = false;

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
    for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it)
    {
        std::string channelName = *it;
        if (hasKey && keyIt != splittedKeys.end())
        {
            key_var = *keyIt;
            if (!key_var.empty() && key_var[0] == ':')
                key_var.erase(0,1);
            ++keyIt;
        }    
        else
            key_var = "";
        if (channelName[0] != '#')
        {
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), channelName, client->get_nickname()));
            continue ;
        }
        if (!channelName[1])
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
            Channel* newChannel = new Channel(channelName, "");
            if (!newChannel->addToChannel(client, ""))
                continue ;
            channels.push_back(newChannel);
            selfJoinReply(client, newChannel);
            sendToChannel(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()), channelName);
        }
        else
        {
            // Channel exists, check key requirement
            Channel* existingChannel = *channelIt;
            std::map<std::string, bool>::iterator it = client->getInvitedChannels().find(existingChannel->getChannelName());
            if (IsClientInChannel(existingChannel->GetClientssHouse(), client->get_fd()))
            {
                SendResponse(client, ERROR_USERONCHANNEL(client->get_hostname(), existingChannel->getChannelName(), client->get_nickname()));
                continue ;
            }
            if (existingChannel->get_l() && existingChannel->GetClientssHouse().size() >= existingChannel->getChannelLimitNum())
            {
                SendResponse(client, ERROR_CHANNELISFULL(client->get_nickname(), existingChannel->getChannelName()));
                continue;
            }
            if (existingChannel->get_k() && existingChannel->getChannelKey().empty())
                continue;
            if(existingChannel->get_i())
            {
                if(it == client->getInvitedChannels().end() || !it->second)
                {
                    SendResponse(client, ERROR_INVITEONLY(client->get_nickname(), existingChannel->getChannelName()));
                    continue;
                }
            }
            if(existingChannel->get_i() && it != client->getInvitedChannels().end())
                it->second = false;
            if (!existingChannel->addToChannel(client, key_var))
                continue ;
            selfJoinReply(client, existingChannel);
            sendToChannel(client, REPLY_JOIN(client->get_nickname(), client->get_username(), channelName, client->get_hostname()), channelName);
        }
    }
    // for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    // {
    //     std::cout << "Channel: " << (*it)->getChannelName() << std::endl;
    //     std::vector<Client*> clientsHouse = (*it)->GetClientssHouse();
    //     if (clientsHouse.empty())
    //     {
    //         std::cout << "No clients in channel: " << (*it)->getChannelName() << std::endl;
    //         continue ;
    //     }

    //     for (std::vector<Client*>::iterator clientIt = clientsHouse.begin(); clientIt != clientsHouse.end(); ++clientIt)
    //     {
    //         std::cout << "Client fd: " << (*clientIt)->get_fd()
    //                   << " nickname: " << (*clientIt)->get_nickname()
    //                   << " operator status: " << (*clientIt)->getIsOperatorStatus() << std::endl;
    //     }
    // }
}
