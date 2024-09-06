#include "../include/server.hpp"

Channel* Server::getChannelByName(std::vector<Channel *> channels, std::string name)
{
    for (size_t i = 0; i < channels.size(); i++)
        if (channels[i]->getChannelName() == name)
            return channels[i];
    return NULL;
}

Client*  NO_CL = NULL;

static Client* staticGetClientByNickplus(std::vector<Client *> clients, std::string nickname)
{
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i]->get_nickname() == nickname)
            return (clients[i]);
   return NO_CL;
}


void Server::KickConstruction(Client *client)
{
    std::vector<std::string> vec = client->get_commande();
    if (vec.size() < 3)
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return ;
    }
    std::vector<std::string> splittedChannels = Splitter(vec[1], ",");
    for(std::vector<std::string>::iterator iterate = splittedChannels.begin() ; iterate != splittedChannels.end(); ++iterate)
    {
        std::string eachChannel = *iterate;
        Channel* check = getChannelByName(channels, eachChannel);
        if (eachChannel[0] != '#')
        {
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
            continue ;
        }
        else if(channeDoesntlExists(channels, eachChannel))
        {
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
            continue ;
        }
        if (staticGetClientByNickplus((check->GetClientssHouse()), client->get_nickname()) && !staticGetClientByNickplus(check->GetClientssHouse(), client->get_nickname())->getIsOperatorStatus())
        {
            SendResponse(client, ERROR_NOPRIVILEGES(client->get_nickname(), client->get_hostname()));
            continue;
        }
        std::vector<std::string> splittedUsers = Splitter(vec[2], ",");
        for (std::vector<std::string>::iterator it = splittedUsers.begin(); it != splittedUsers.end(); ++it)
        {
            std::string eachUser = *it;
            if (!isClientExist(clients, eachUser))
                SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(),client->get_nickname(), eachUser));
            else if (getClientByNick(clients, eachUser).get_fd())
            {
                Client& target = getClientByNick(clients, eachUser);
                Channel* channelPtr = getChannelByName(channels, eachChannel);
                if (!channelPtr)
                    return ;
                if (vec.size() == 3)
                    vec.push_back("no comment is given");
                Channel& channel = *channelPtr;
                channel.removeFromChannel(&target);
                std::string rpl = REPLY_KICK(client->get_nickname(), client->get_username(), \
                target.get_hostname(), channel.getChannelName(), target.get_nickname(), vec[3]);
                SendResponse(&target, rpl);
                sendToChannel(&target, rpl, channel.getChannelName());
                deleteTheChannelWhenNoUserInIt(&channel);
            }
        }
    }
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        std::vector<Client*> clientsHouse = (*it)->GetClientssHouse();
        if (clientsHouse.empty())
            continue ;
    }
}
