#include "../include/server.hpp"

void  	Server::PartConstruction(Client *client)
{   
    std::vector<std::string> vec = client->get_commande();
    if (vec.size() < 2)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    else if (vec[1][0] != '#')
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[1], client->get_nickname()));
    else if(channeDoesntlExists(channels, vec[1]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[1], client->get_nickname()));
    else
    {
        Channel* channelPtr = getChannelByName(channels, vec[1]);
        if (!channelPtr)
            return ;
        if (vec.size() == 2)
            vec.push_back("no comment is given");
        Channel& channel = *channelPtr;
        channel.removeFromChannel(client);
        std::string rpl = PART_REPLY(vec[1], client->get_nickname(), vec[2]);
        SendResponse(client, rpl);
        std::cout << rpl << std::endl;
        // client.getInvitedChannels().push_back(vec[1]);
        // REMINDER : should broadcast to all clients in the channel
    }
}   