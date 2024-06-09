#include  "../include/server.hpp"


// static bool AtleastOneClient()
// {
//     Channel channel;
//     if(channel.GetClientssHouse().size() > 0)
//         return true;
//     return false;
// }


Client& Server::getClientByNick(std::vector<Client> &clients, std::string nickname)
{
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].get_nickname() == nickname)
            return (clients[i]);
   throw std::runtime_error("Client not found");
}

bool isClientExist(std::vector<Client> clients, std::string nickname)
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
    else if (vec[2][0] != '#')
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
    else if(channelExists(channels, vec[2]))
        SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
    else if (!isClientExist(clients, vec[1]))
        SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(),client->get_nickname(), vec[1]));
    else if (getClientByNick(clients, vec[1]).get_fd())
    {
        std::cout << "InviteConstruction" << std::endl;
        Client& target = getClientByNick(clients, vec[1]);
        Channel invitted(vec[2]);
        invitted.addToChannel(client);
        target.get_accessibleChannels().push_back(vec[2]);
        // REPLY_INVITE(client->get_nickname(), client->get_username(), client->get_hostname() ,vec[1], vec[2])
        std::string rpl = REPLY_INVITE(target.get_nickname(), target.get_username(), target.get_hostname(), vec[1], vec[2]);
        std::cout << rpl << std::endl;
        SendResponse(&target, rpl);
        std::cout <<"heeeeeeeeeere" << target.get_accessibleChannels().size() << std::endl;
    }
}

// void Server::InviteConstruction(Client *client)
// {
//     std::vector<std::string> vec = client->get_commande();
//     if (vec.size() < 3)
//         SendResponse(client, ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname()));
//     else if (vec[2][0] != '#')
//         SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
//     else if (channelExists(channels, vec[2]))
//         SendResponse(client, ERROR_NOSUCHCHANNEL(client->get_hostname(), vec[2], client->get_nickname()));
//     else if (!isClientExist(clients, vec[1]))
//         SendResponse(client, ERROR_NOSUCHNICK(client->get_hostname(),client->get_nickname(), vec[1]));
//     else if (getClientByNick(clients, vec[1]))
//     {
//         std::cout << "InviteConstruction" << std::endl;
//         Client& target = getClientByNick(clients, vec[1]);
//         Channel invitted(vec[2]);
//         invitted.addToChannel(client);
//         target.get_accessibleChannels().push_back(vec[2]);
//         // REPLY_INVITE(client->get_nickname(), client->get_username(), client->get_hostname() ,vec[1], vec[2])
//         std::string rpl = REPLY_INVITE(target.get_nickname(), target.get_username(), target.get_hostname(), vec[1], vec[2]);
//         std::cout << rpl << std::endl;
//         SendResponse(&target, rpl);
//     }
// }  