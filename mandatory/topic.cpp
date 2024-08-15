/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:03:45 by azgaoua           #+#    #+#             */
/*   Updated: 2024/08/15 16:13:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/reply.hpp"
#include "../include/channels.hpp"


int Server::no_suck_channel(std::vector<std::string> Topic)
{
    if (channels.size() == 0)
        return (1);
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->getChannelName() == Topic[1])
            return (0);
    }
    return (1);
}

int Server::on_channel(std::vector<Client *>  Clnts, Client *nick)
{
    if (Clnts.size() == 0)
        return (0);
    for (std::vector<Client *>::iterator it = Clnts.begin(); it != Clnts.end(); ++it)
    {
        if ((*it)->get_nickname() == nick->get_nickname())
            return(1);
    }
    return (0);
}

void    Server::Topic_Command(std::vector<std::string> Topic, Client *user) {
    std::string full_name_topic;
    if (Topic[1][0] == '#') {
        if (no_suck_channel(Topic) == 1)
        {
            sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), Topic[1], user->get_nickname()));
            return ;
        }
        for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
            if ((*it)->getChannelName() == Topic[1])
            {
                std::vector<Client *> Clnts = (*it)->GetClientssHouse();
                if (on_channel(Clnts, user) == 0)
                    break ;
                if (Topic[2][0] == ':')
                {
                    Topic[2].erase(0, 1);
                    for (size_t j = 2; j < Topic.size(); j++)
                        full_name_topic += Topic[j];
                    if (full_name_topic.empty())
                    {
                        sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), Topic[1], ""));
                        // REPLY_TOPICWHOTIME
                        (*it)->set_topic("");
                    }
                    else
                    {
                        sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), Topic[1], full_name_topic));
                        // REPLY_TOPICWHOTIME
                        (*it)->set_topic(full_name_topic);
                    }
                }
                else if (Topic.size() >= 3)
                {
                    full_name_topic += Topic[2];
                    if (full_name_topic.empty())
                    {
                        sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), Topic[1], ""));
                        // REPLY_TOPICWHOTIME
                        (*it)->set_topic("");
                    }
                    else
                    {
                        sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), Topic[1], full_name_topic));
                        // REPLY_TOPICWHOTIME
                        (*it)->set_topic(full_name_topic);
                    }
                }
                return;
            }
        }
        sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), Topic[1], user->get_nickname()));
    }
    else
        std::cerr << "Error: No such channel (syntax `#`)"<< std::endl;
}

std::string Channel::get_topic() {
    return (topic);
}

void Channel::set_topic(std::string topic)
{
    this->topic = topic;
}

void Server::DisplayTopic(std::vector<std::string> channel_name, Client *user) {
    std::vector<Channel*>::iterator k;

    if (channel_name.size() == 1)
    {
        std::string command = channel_name[0];
        sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), user->get_hostname()));
        return ;
    }
    for (k = channels.begin(); k != channels.end(); ++k) {
        if ((*k)->getChannelName() == channel_name[1]) {
            std::vector<Client *> Clnts = (*k)->GetClientssHouse();
            if (on_channel(Clnts, user) == 0)
                break ;
            if ((*k)->get_topic().empty())
                sendToClient(user->get_fd(), RPL_NOTOPIC(user->get_hostname(), channel_name[1]));
            else
                sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), channel_name[1], (*k)->get_topic()));
            return ;
        }
    }
    if (k == channels.end())
        sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), channel_name[1], user->get_nickname()));
    else
        sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), channel_name[1], user->get_nickname()));
}
