#include "../include/server.hpp"
#include "../include/reply.hpp"
#include "../include/channels.hpp"

int Server::no_suck_channel_msg(std::string chnl)
{
    if (channels.size() == 0)
        return (1);
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->getChannelName() == chnl)
            return (0);
    }
    return (1);
}

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

std::vector<std::string> split(std::string command, char delimeter)
{
    std::stringstream ss(command);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
       splittedStrings.push_back(item);
    return splittedStrings;
}

void Server::Private_message(std::vector<std::string> command, Client *user)
{
    std::vector<std::string> targets;
    std::string full_message;
    size_t i;

    if (command.size() <= 2 || (command.size() == 3 && command[1] == ":"))
    {
        sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
        return ;
    }
    targets =  split(command[1], ',');
    for(std::vector<std::string>::iterator it_t = targets.begin(); it_t != targets.end(); ++it_t)
    {
        if ((*it_t)[0] == '#')
        {
            if (no_suck_channel_msg((*it_t)) == 1)
            {
                sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), \
                                (*it_t), user->get_nickname()));
                continue ;
            }
            for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
            {
                if ((*it)->getChannelName() == (*it_t))
                {
                    if (on_channel((*it)->GetClientssHouse(), user))
                    {
                        if (command[2] == ":")
                            command.erase(command.begin() + 2);
                        full_message = command[2];
                        if (full_message.empty())
                            sendToChannel(user, ERR_NOTEXTTOSEND(user->get_hostname()), (*it)->getChannelName());
                        else
                            sendToChannel(user, RPL_AWAY(user->get_nickname() , user->get_username(), \
                                            user->get_hostname(), full_message, (*it)->getChannelName()), \
                                                (*it)->getChannelName());
                        continue ;
                    }
                    else
                        sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), \
                                        (*it)->getChannelName(), user->get_nickname()));
                }
            }
        }
        else
        {
            for (i = 0; i < clients.size(); i++)
            {
                if (clients[i].get_nickname() == (*it_t) && clients[i].is_enregistred())
                {
                    if (command[2] == ":")
                        command.erase(command.begin() + 2);
                    full_message = command[2];
                    if (full_message.empty())
                        sendToClient(user->get_fd(), ERR_NOTEXTTOSEND(user->get_hostname()));
                    else
                        sendToClient(clients[i].get_fd(), RPL_AWAY(user->get_nickname(), \
                                        user->get_username(), user->get_hostname(), full_message, \
                                            clients[i].get_nickname()));
                    break ;
                }
            }
            if (i >= clients.size())
                sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), (*it_t)));
        }
    }
}