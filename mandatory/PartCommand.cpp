#include "../include/server.hpp"

void  	Server::PartConstruction(Client *client)
{   
    std::vector<std::string> vec = client->get_commande();
    std::vector<std::string> splittedChannels = Splitter(vec[1], ",");
    if (vec.size() < 2)
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return ;
    }
    for (std::vector<std::string>::iterator it = splittedChannels.begin(); it != splittedChannels.end(); ++it)
    {
        std::string eachChannel = *it;
        if (eachChannel[0] != '#')
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
        else if (channeDoesntlExists(channels, eachChannel))
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
        else if (!IsClientInChannel(getChannelByName(channels, eachChannel)->GetClientssHouse(), client->get_fd()))
            SendResponse(client, ERROR_NOTONCHANNEL(client->get_hostname(), eachChannel));
        else
        {
            Channel* channelPtr = getChannelByName(channels, eachChannel);
            if (!channelPtr)
                return ;
            if (vec.size() == 2)
                vec.push_back("no comment is given");
            Channel& channel = *channelPtr;
            channel.removeFromChannel(client);
            SendResponse(client, PART_REPLY(client->get_nickname(), client->get_hostname(), client->get_username(), eachChannel));
            for (std::vector<Channel *>::iterator itrem = channels.begin(); itrem != channels.end(); ++itrem)
            {
                Channel* tmp = *itrem;
                if (tmp == &channel && channel.GetClientssHouse().size() == 0)
                {
                    channels.erase(itrem);
                    break;
                }
            }
        }
    }
    
}
