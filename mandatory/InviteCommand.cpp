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
        SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
    else if(vec[2][0] != '#' || channeDoesntlExists(channels, vec[2]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
    else if (!isClientExist(clients, vec[1]))
        SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(),client->get_nickname(), vec[1]));
    else if(IsClientInChannel(getChannelByName(channels, vec[2])->GetClientssHouse(), getClientByNick(clients, vec[1]).get_fd()))
        SendResponse(client, ERROR_USERONCHANNEL(getClientByNick(clients, vec[1]).get_hostname(), vec[2], getClientByNick(clients, vec[1]).get_nickname()));
    else if (getChannelByName(channels, vec[2])->get_i() && getClientByNick(clients, vec[1]).get_fd() && !getClientByNick(clients, vec[1]).getIsOperatorStatus())
        SendResponse(client, ERROR_NOPRIVILEGES(client->get_hostname(), vec[2]));
    else if (getChannelByName(channels, vec[2])->get_i() == false && getClientByNick(clients, vec[1]).get_fd())
    {
        Client& target = getClientByNick(clients, vec[1]);
        target.getInvitedChannels()[vec[2]] = true;
        SendResponse(client , REPLY_INVITING(client->get_hostname(), client->get_nickname(), target.get_nickname(), vec[2]));
        SendResponse(&target, REPLY_INVITE(target.get_nickname(), target.get_username(), target.get_hostname(), vec[1], vec[2]));
    }
}