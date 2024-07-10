#include "../include/server.hpp"

std::vector<std::string> Splitter(std::string cmd, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;
    while ((pos = cmd.find(delimiter)) != std::string::npos)
    {
        token = cmd.substr(0, pos);
        result.push_back(token);
        cmd.erase(0, pos + delimiter.length());
    }
    result.push_back(cmd);
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

// 
void Server::JoinConstruction(Client *client) {
    Channel channel("default");
    std::vector<std::string> cmd = client->get_commande();

    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1]) {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return;
    }

    std::vector<std::string> channelNames = Splitter(cmd[1], ",");
    for (size_t i = 0; i < channelNames.size(); i++) {
        if (channelNames[i][0] != '#') {
            SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), channelNames[i], client->get_nickname()));
        } else if (channeDoesntlExists(channels, channelNames[i])) {
            // Channel doesn't exist, create new channel and add client
            Channel newChannel(channelNames[i]);
            newChannel.addToChannel(client);
            channels.push_back(newChannel);
            client->getInvitedChannels().push_back(channelNames[i]);
            SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), client->get_hostname(), channelNames[i]));
            std::cout << "Channel created: " << channelNames[i] << " with client: " << client->get_nickname() << std::endl;
        } else {
            // Channel exists, add client to the channel
            for (size_t j = 0; j < channels.size(); j++) {
                if (channels[j].getChannelName() == channelNames[i]) {
                    channels[j].addToChannel(client);
                    client->getInvitedChannels().push_back(channelNames[i]);
                    SendResponse(client, REPLY_JOIN(client->get_nickname(), client->get_username(), client->get_hostname(), channelNames[i]));
                    std::cout << "Client " << client->get_nickname() << " joined existing channel: " << channelNames[i] << std::endl;
                }
            }
        }
    }

    for (size_t i = 0; i < channels.size(); i++) {
        if (!channels[i].GetClientssHouse().empty()) {
            for (size_t j = 0; j < channels[i].GetClientssHouse().size(); j++) {
                std::cout << "clients fd : " << channels[i].GetClientssHouse()[j]->get_fd()
                          << " operator status : " << channels[i].GetClientssHouse()[j]->getIsOperatorStatus() << std::endl;
            }
        } else {
            std::cout << "No clients in the first channel or no channels available." << std::endl;
        }
    }
}
