#include "../include/server.hpp"


void Server::deleteTheChannelWhenNoUserInIt(Channel *channel)
{
    for (std::vector<Channel *>::iterator itrem = channels.begin(); itrem != channels.end(); ++itrem)
    {
        Channel* tmp = *itrem;
        if (tmp == channel && channel->GetClientssHouse().size() == 0)
        {
            delete (*itrem);
            channels.erase(itrem);
            break;
        }
    }
}

void  	Server::PartConstruction(Client *client)
{   
    std::vector<std::string> vec = client->get_commande();
    std::vector<std::string> splittedChannels;
    if (vec.size() < 2)
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return ;
    }
    if (vec[1] == ":" && vec.size() == 3)
        splittedChannels = Splitter(vec[2], ",");
    else
        splittedChannels = Splitter(vec[1], ",");
    for (std::vector<std::string>::iterator it = splittedChannels.begin(); it != splittedChannels.end(); ++it)
    {
        std::string eachChannel = *it;
        if (eachChannel[0] != '#' || eachChannel.substr(1).find(" ") != std::string::npos)
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
        else if (channeDoesntlExists(channels, eachChannel))
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
        else if (!IsClientInChannel(getChannelByName(channels, eachChannel)->GetClientssHouse(), client->get_fd()))
            SendResponse(client, ERROR_NOTONCHANNEL(client->get_hostname(), eachChannel));
        else
        {
            Channel* channelPtr = getChannelByName(channels, eachChannel);
            std::string reason;
            if (!channelPtr)
                return ;
            if (vec.size() == 2)
                reason = "";
            else if(vec.size() >= 3 && vec[2] == ":")
                reason = vec[3];
            Channel& channel = *channelPtr;
            channel.removeFromChannel(client);
            SendResponse(client, PART_REPLY(client->get_nickname(), client->get_hostname(), client->get_username(), eachChannel, reason));
            sendToChannel(client, PART_REPLY(client->get_nickname(), client->get_hostname(), client->get_username(), eachChannel, reason), channel.getChannelName());
            deleteTheChannelWhenNoUserInIt(&channel);
        }
    }
    
}
