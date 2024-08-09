#include "../include/server.hpp"

Channel* getChannelByName(std::vector<Channel *> channels, std::string name)
{
    for (size_t i = 0; i < channels.size(); i++)
        if (channels[i]->getChannelName() == name)
            return channels[i];
    return NULL;
}


void Server::KickConstruction(Client *client)
{
    std::vector<std::string> vec = client->get_commande();
    if (!client->getIsOperatorStatus()) 
    {
        SendResponse(client, ERROR_NOPRIVILEGES(client->get_nickname(), client->get_hostname()));
        return;
    }
    if (vec.size() < 4)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    else if (vec[1][0] != '#')
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[1], client->get_nickname()));
    else if(channeDoesntlExists(channels, vec[1]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[1], client->get_nickname()));
    else if (!isClientExist(clients, vec[2]))
        SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(),client->get_nickname(), vec[2]));
    else if (getClientByNick(clients, vec[2]).get_fd())
    {
        Client& target = getClientByNick(clients, vec[2]);
        Channel* channelPtr = getChannelByName(channels, vec[1]);
        if (!channelPtr)
            return ;
        Channel& channel = *channelPtr;
        channel.removeFromChannel(&target, "KICK");
        target.getInvitedChannels().push_back(vec[1]);
        std::string rpl = REPLY_KICK(target.get_nickname(), target.get_username(), target.get_hostname(), vec[2], vec[1], vec[3]);
        SendResponse(&target, rpl);
        SendResponse(, rpl);
        std::cout << rpl << std::endl;
        // REMINDER : should broadcast to all clients in the channel
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
            std::cout << "Client fd: " << (*clientIt)->get_fd()
                    << " nickname: " << (*clientIt)->get_nickname()
                    << " operator status: " << (*clientIt)->getIsOperatorStatus() << std::endl;
    }
}
