#include "../include/server.hpp"

bool channelExists(std::vector<Channels> haystack, std::string needle)
{
    for (size_t i = 0; i < haystack.size(); i++)
        if (haystack[i].getChannelName() == needle)
            return false;
    return true;
}

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

void Server::JoinConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();
    std::string msg = ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname());
    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1])
    {
        if (send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
        return ;
    }
    std::vector<std::string> channelNames = Splitter(cmd, ",");
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        if(channelNames[i][0] != '#')
        {
            msg = ERROR_NOSUCHCHANNEL(client->get_hostname(), channelNames[i], client->get_nickname());
            std::cout << msg << std::endl;
            if (send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
                throw std::runtime_error("Failed Send JOIN message to the client");
        }
        else if(channelExists(channels, channelNames[i]))
        {
            Channels channel(channelNames[i]);
            channel.join(client);
            channels.push_back(channel);
        }
    }
    for(size_t i = 0; i < channels.size(); i++)
        std::cout << ""<< "channel: " << channels[i].getChannelName() << std::endl;
    // for(size_t i = 0; i < clients.size(); i++)
    //     std::cout << "client: " << clients[i].get_fd() << std::endl;
    // std::cout<< "Client joined "<< cmd[1] << " successfully !" << std::endl;
}