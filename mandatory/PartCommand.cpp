#include "../include/server.hpp"

void  	Server::PartConstruction(Client *client)
{   
    std::vector<std::string> vec = client->get_commande();
    std::vector<std::string> splittedChannels = Splitter(vec[1], ",");
    if (vec.size() < 2)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    for (std::vector<std::string>::iterator it = splittedChannels.begin(); it != splittedChannels.end(); ++it)
    {
        std::string eachChannel = *it;
        if (eachChannel[0] != '#')
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
        else if (channeDoesntlExists(channels, eachChannel))
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), eachChannel, client->get_nickname()));
        else
        {
            Channel* channelPtr = getChannelByName(channels, eachChannel);
            if (!channelPtr)
                return ;
            if (vec.size() == 2)
                vec.push_back("no comment is given");
            Channel& channel = *channelPtr;
            channel.removeFromChannel(client);
            std::string rpl = PART_REPLY(eachChannel, client->get_nickname(), vec[2]);
            SendResponse(client, rpl);
            std::cout <<  ":" << eachChannel << " " << client->get_nickname() << " has left (" << vec[2] << ")" << std::endl;
            // client.getInvitedChannels().push_back(vec[1]);
            // REMINDER : should broadcast to all clients in the channel
        }
    }
}   