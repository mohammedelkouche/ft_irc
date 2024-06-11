#include "../include/server.hpp"


void Server::KickConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();
    std::vector<std::string> secondParam;
    secondParam.push_back((cmd[1]));
    if (cmd.size() < 3)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), cmd[0]));
    else if (cmd[0] != "#" || channeDoesntlExists(channels, cmd[0]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_nickname(), client->get_hostname(), cmd[0]));
    else if(std::find(secondParam.begin(), secondParam.end(), ",") != secondParam.end())
    {
        std::vector<std::string> users = Splitter(secondParam ,",");
        for (size_t i = 0; i < users.size(); i++)
        {
            if(isClient)
        }
        // std::string channelName = cmd[1];
        // std::string nickname = cmd[2];
        // if (!channeDoesntlExists(channels, channelName))
        //     SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_nickname(), channelName));
    }
}