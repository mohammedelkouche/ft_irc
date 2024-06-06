#include  "../include/server.hpp"


// static bool AtleastOneClient()
// {
//     if ()
//         return true;
//     return false;
// }

void Server::InviteConstruction(Client *client)
{
    std::vector<std::string> vec = client->get_commande();
    if (vec.size() < 3)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    else if (vec[2][0] != '#')
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
    else if (channelExists(channels, vec[2]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
    else if (!channelExists(channels, vec[2]) && !channels[0].GetClientssHouse().size())
    {
        client->getAccessedChannels().push_back(vec[2]);
        SendResponse(client, REPLY_INVITE(client->get_nickname(), client->get_username(), client->get_hostname() ,vec[1], vec[2]));
    }
    else
        std::cout << "mal9ahach" << std::endl;
}  