#include "../include/server.hpp"


void Server::KickConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();
    std::vector<std::string> secondParam;
    secondParam.push_back((cmd[1]));
    if(!client->getIsOperatorStatus())
        throw std::runtime_error("Sorry! you don't have permession");
    if (cmd.size() < 3)
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), cmd[0]));
    else if (cmd[0] != "#" || channeDoesntlExists(channels, cmd[0]))
    {
        std::cout << "statement 1" << std::endl;
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_nickname(), client->get_hostname(), cmd[0]));
    }
    // else if(std::find(secondParam.begin(), secondParam.end(), ",") == secondParam.end())
    // {
    //     if(IsClientInChannel(channels[0].GetClientssHouse(), client->get_fd()))
    //         channels[0].removeFromChannel(client, cmd[2]);
    //     else if(!IsClientInChannel(channels[0].GetClientssHouse(), client->get_fd()))
    //     {
    //         std::cout << "statement 2" << std::endl;
    //         SendResponse(client, ERROR_NOTONCHANNEL(client->get_nickname(), channels[0].getChannelName()));
    //     }
    // }
    else if(std::find(secondParam.begin(), secondParam.end(), ",") != secondParam.end())
    {
        std::vector<std::string> users = Splitter(secondParam ,",");
        for (size_t i = 0; i < users.size(); i++)
        {
            if(IsClientInChannel(channels[i].GetClientssHouse(), client->get_fd()))
                channels[i].removeFromChannel(client, cmd[2]);
            else if(!IsClientInChannel(channels[i].GetClientssHouse(), client->get_fd()))
            {
                std::cout << "statement 2" << std::endl;
                SendResponse(client, ERROR_NOTONCHANNEL(client->get_nickname(), channels[i].getChannelName()));
            }
        }
    }

}