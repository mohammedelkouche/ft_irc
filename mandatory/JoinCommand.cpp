#include "../include/server.hpp"

std::vector<std::string> Splitter(std::vector<std::string> cmd, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;
    // int i = 0;
    while ((pos = cmd[1].find(delimiter)) != std::string::npos)
    {
        token = cmd[1].substr(0, pos);
        result.push_back(token);
        cmd[1].erase(0, pos + delimiter.length());

    }
    result.push_back(cmd[1]);
    return result;
}

bool Server::channeDoesntlExists(std::vector<Channel> haystack, std::string needle)
{
    for (size_t i = 0; i < haystack.size(); i++)
        if (haystack[i].getChannelName() == needle)
            return false;
    return true;
}


void SendResponse(Client *client, std::string msg)
{
    if (send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
        throw std::runtime_error("Failed Send JOIN message to the client");
}

void Server::JoinConstruction(Client *client)
{
    Channel channel("channel");
    std::vector<std::string> cmd = client->get_commande();
    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1])
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    std::vector<std::string> channelNames = Splitter(cmd, ",");
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        if(channelNames[i][0] != '#')
        {
            std::cout << ERROR_NOSUCHCHANNEL(client->get_hostname(), channelNames[i], client->get_nickname()) << std::endl;
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), channelNames[i], client->get_nickname()));
        }
        else if (channeDoesntlExists(channels, channelNames[i]) && !channel.GetClientssHouse().size())
        {
            channel.setChannelName(channelNames[i]);
            client->setOperatorStatus(true);
            channel.addToChannel(client);
            channels.push_back(channel);
            std::cout << REPLY_JOIN(client->get_nickname(), client->get_username(), client->get_hostname(), channelNames[i]) << std::endl;
            SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), client->get_hostname(), channelNames[i]));
        }
        else if(channeDoesntlExists(channels, channelNames[i]))
        {
            Channel channel(channelNames[i]);
            channel.addToChannel(client);
            channels.push_back(channel);
        }
    }
    for(size_t i = 0; i < channels.size(); i++)
        std::cout << ""<< "channel: " << channels[i].getChannelName() << "Operator Status: " <<  client->getIsOperatorStatus() << std::endl;
// for(size_t i = 0; i < clients.size(); i++)
//     std::cout << "client: " << clients[i].get_fd() << std::endl;
// std::cout<< "Client joined "<< cmd[1] << " successfully !" << std::endl;
}