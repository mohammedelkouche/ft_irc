#include "../include/server.hpp"

Channel* Server::getChannelByName(std::vector<Channel *> channels, std::string name)
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
    if (vec.size() < 3)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    else if (vec[1][0] != '#')
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[1], client->get_nickname()));
    else if(channeDoesntlExists(channels, vec[1]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[1], client->get_nickname()));
    std::vector<std::string> splittedUsers = Splitter(vec[2], ",");
    for (std::vector<std::string>::iterator it = splittedUsers.begin(); it != splittedUsers.end(); ++it)
    {
        std::string eachUser = *it;
        if (!isClientExist(clients, eachUser))
            SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(),client->get_nickname(), eachUser));
        else if (getClientByNick(clients, eachUser).get_fd())
        {
            Client& target = getClientByNick(clients, eachUser);
            Channel* channelPtr = getChannelByName(channels, vec[1]);
            if (!channelPtr)
                return ;
            if (vec.size() == 3)
                vec.push_back("no comment is given");
            Channel& channel = *channelPtr;
            channel.removeFromChannel(&target);
            std::string rpl = REPLY_KICK(client->get_nickname(), client->get_username(), \
            target.get_hostname(), channel.getChannelName(), target.get_nickname(), vec[3]);
            SendResponse(&target, rpl);
            // REMINDER : should broadcast to all clients in the channel
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
            std::cout << "Client fd: " << (*clientIt)->get_fd()
                    << " nickname: " << (*clientIt)->get_nickname()
                    << " operator status: " << (*clientIt)->getIsOperatorStatus() << std::endl;
    }
}
