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

std::vector<std::string> split(std::string commande, char delimeter)
{
    std::stringstream ss(commande);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
       splittedStrings.push_back(item);
    return splittedStrings;
}

void Server::Private_message(std::vector<std::string> commande, Client *user)
{
    std::vector<std::string> targets;
    std::string full_message;
    size_t i;

    targets =  split(commande[1], ',');

    if (commande.size() <= 2)
    {
        sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
        return ;
    }
    for(std::vector<std::string>::iterator it_t = targets.begin(); it_t != targets.end(); ++it_t)
    {
        if ((*it_t)[0] == '#')
        {
            if (no_suck_channel(commande) == 1)
            {
                sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), (*it_t), user->get_nickname()));
                continue ;
            }
            for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
            {
                if ((*it)->getChannelName() == (*it_t))
                {
                    if (on_channel((*it)->GetClientssHouse(), user))
                    {
                        if (commande[2][0] == ':')
                        {
                            commande[2].erase(0, 1);
                            for (size_t j = 2; j < commande.size(); j++)
                                full_message += commande[j];
                        }
                        else
                            full_message += commande[2];
                        if (full_message.empty())
                            sendToChannel(user, ERR_NOTEXTTOSEND(user->get_hostname()), (*it)->getChannelName());
                        else
                            sendToChannel(user, RPL_AWAY(user.get ,(*it)->getChannelName(), user->get_hostname(), full_message), (*it)->getChannelName());
                        continue ;
                    }
                    else
                        sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), (*it)->getChannelName(), user->get_nickname()));
                }
            }
        }
        else
        {
            for (i = 0; i < clients.size(); i++)
            {
                if (clients[i].get_nickname() == (*it_t))
                {
                    if (commande[2][0] == ':')
                    {
                        commande[2].erase(0, 1);
                        for (size_t j = 2; j < commande.size(); j++)
                            full_message += commande[j];
                        if (full_message.empty())
                            sendToClient(user->get_fd(), ERR_NOTEXTTOSEND(user->get_hostname()));
                        else
                            sendToClient(clients[i].get_fd(), RPL_AWAY(clients[i].get_nickname(), user->get_hostname(), full_message));
                    }
                    else
                    {
                        full_message += commande[2];
                        if (full_message.empty())
                            sendToClient(user->get_fd(), ERR_NOTEXTTOSEND(user->get_hostname()));
                        else
                            sendToClient(clients[i].get_fd(), RPL_AWAY(clients[i].get_nickname(), user->get_hostname(), full_message));
                    }
                    break ;
                }
            }
            if (i >= clients.size())
                sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), (*it_t)));
        }
    }
}