#include "../include/server.hpp"
#include "../include/reply.hpp"
#include "../include/channels.hpp"

void Server::sendToChannel(Client *user, const std::string& message, std::string Chnl)
{
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->getChannelName() == Chnl)
        {
            for (size_t i = 0; i < (*it)->GetClientssHouse().size(); i++)
            {
                if ((*it)->GetClientssHouse()[i]->get_nickname() != user->get_nickname())
                    sendToClient((*it)->GetClientssHouse()[i]->get_fd(), message);
            }
        }
    }
}

void Server::Private_message(std::vector<std::string> commande, Client *user)
{
    std::string full_message;
    size_t i;

    if (commande.size() == 1)
    {
        sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
        return ;
    }
    if (commande[1][0] == '#')
    {
        if (no_suck_channel(commande) == 1)
        {
            sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), commande[1], user->get_nickname()));
            return ;
        }
        for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
        {
            if ((*it)->getChannelName() == commande[1])
            {
                if (on_channel((*it)->GetClientssHouse(), user))
                {
                    if (commande.size() >= 3 && commande[2][0] == ':')
                    {
                        commande[2].erase(0, 1);
                        for (size_t j = 2; j < commande.size(); j++)
                            full_message += commande[j];
                    }
                    else if (commande.size() >= 3)
                        full_message += commande[2];
                    if (full_message.empty())
                        sendToChannel(user, ERR_NOTEXTTOSEND(user->get_hostname()), (*it)->getChannelName());
                    else
                        sendToChannel(user, RPL_AWAY(commande[1], user->get_hostname(), full_message), (*it)->getChannelName());
                    return ;
                }
                else
                    sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), commande[1], user->get_nickname()));
            }
        }
    }
    else
    {
        for (i = 0; i < clients.size(); i++)
        {
            if (clients[i].get_nickname() == commande[1])
            {
                if (commande[2][0] == ':')
                {
                    commande[2].erase(0, 1);
                    for (size_t j = 2; j < commande.size(); j++)
                        full_message += commande[j];
                    if (full_message.empty())
                        sendToClient(user->get_fd(), ERR_NOTEXTTOSEND(user->get_hostname()));
                    else
                        sendToClient(clients[i].get_fd(), RPL_AWAY(commande[1], user->get_hostname(), full_message));
                }
                else
                {
                    full_message += commande[2];
                    if (full_message.empty())
                        sendToClient(user->get_fd(), ERR_NOTEXTTOSEND(user->get_hostname()));
                    else
                        sendToClient(clients[i].get_fd(), RPL_AWAY(commande[1], user->get_hostname(), full_message));
                }
                return ;
            }
        }
        if (i >= clients.size())
            sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), user->get_nickname()));
    }
}