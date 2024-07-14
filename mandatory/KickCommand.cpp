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
        std::cout << ERROR_NOPRIVILEGES(client->get_nickname(), client->get_hostname()) << std::endl;
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
        std::cout << rpl << std::endl;
        // REMINDER : should broadcast to all clients in the channel
    }
    else
        std::cout << "Client not kicked" << std::endl;
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

// std::vector<std::string> cmd = client->get_commande();
// std::vector<std::string> secondParam;
// secondParam.push_back((cmd[1]));
// if(!client->getIsOperatorStatus())
//     return ;
// if (cmd.size() < 4)
// {
//     SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
//     return ;
// }
// if (cmd[1][0] != '#' || channeDoesntlExists(channels, cmd[1]))
// {
//     std::cout << "statement 1" << std::endl;
//     SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_nickname(), client->get_hostname(), cmd[1]));
//     return ;
// }
// std::vector<std::string> users = Splitter(secondParam[1] ,",");
// for (size_t i = 0; i < users.size(); i++)
// {
//     std::cout << " ---------------------> IsClientInChannel " << IsClientInChannel(channels[i].GetClientssHouse(), client->get_fd()) << std::endl;
//     if(IsClientInChannel(channels[i].GetClientssHouse(), client->get_fd()))
//         channels[i].removeFromChannel(client, cmd[3]);
//     else if(!IsClientInChannel(channels[i].GetClientssHouse(), client->get_fd()))
//     {
//         std::cout << "statement 3" << std::endl;
//         SendResponse(client, ERROR_NOTONCHANNEL(client->get_nickname(), channels[i].getChannelName()));
//     }
// }
