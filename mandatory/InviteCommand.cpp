#include  "../include/server.hpp"

Client NO_CLIENT;

Client& Server::getClientByNick(std::vector<Client> &clients, std::string nickname)
{
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].get_nickname() == nickname)
            return (clients[i]);
   return NO_CLIENT;
}

bool Server::isClientExist(std::vector<Client> clients, std::string nickname)
{
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].get_nickname() == nickname)
            return true;
    return false;
}

void Server::InviteConstruction(Client *client)
{
    std::vector<std::string> vec = client->get_commande();
    
    if (vec.size() < 3)
    {
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
        return;
    }
    std::string targetNick = (vec.size() >= 4 && vec[1] == ":") ? vec[2] : vec[1];
    std::string channelName =  (vec.size() >= 4 && vec[2] == ":") ? vec[3] : vec[2];
    if (!isClientExist(clients, targetNick) || targetNick.find(' ', 0) != std::string::npos)
    {
        SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(), client->get_nickname(), targetNick));
        return;
    }
    if (channelName[0] != '#' || channeDoesntlExists(channels, channelName) || channelName.find(' ', 0) != std::string::npos)
    {
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), channelName, client->get_nickname()));
        return;
    }

    Channel* channel = getChannelByName(channels, channelName);
    Client& target = getClientByNick(clients, targetNick);

    if (!IsClientInChannel(channel->GetClientssHouse(), client->get_fd()))
    {
        SendResponse(client, ERROR_NOTONCHANNEL(client->get_hostname(), channelName));
        return;
    }
    if (IsClientInChannel(channel->GetClientssHouse(), target.get_fd()))
    {
        SendResponse(client, ERROR_USERONCHANNEL(target.get_hostname(), channelName, target.get_nickname()));
        return;
    }
    if (channel->get_i())
    {
        if (staticGetClientByNickplus((channel->GetClientssHouse()), client->get_nickname()) && \
            !staticGetClientByNickplus(channel->GetClientssHouse(), client->get_nickname())->getIsOperatorStatus())
        {
            SendResponse(client, ERROR_NOPRIVILEGES(client->get_hostname(), channelName));
            return;
        }
    }
    target.getInvitedChannels()[channelName] = true;
    SendResponse(client, REPLY_INVITING(client->get_hostname(), client->get_nickname(), target.get_nickname(), channelName));
    SendResponse(&target, REPLY_INVITE(target.get_nickname(), target.get_username(), target.get_hostname(), client->get_nickname(), channelName));
}
