#include "../include/server.hpp"


void Server::KickConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();
    if (cmd.size() < 3)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), cmd[0]));
    else if (cmd[0] != "#")
        SendResponse(client, ERROR_UNKNOWNCOMMAND(client->get_nickname(), client->get_hostname(), cmd[0]));
    else
    {
        // std::string channelName = cmd[1];
        // std::string nickname = cmd[2];
        // if (!channelExists(channels, channelName))
        //     SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_nickname(), channelName));
    }
}