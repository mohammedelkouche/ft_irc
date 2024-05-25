/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:03:45 by azgaoua           #+#    #+#             */
/*   Updated: 2024/05/24 02:57:07 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/topic.hpp"
#include "../include/server.hpp"
#include "../include/reply.hpp"


void    Server::Topic_Command(std::vector<std::string> Topic, Client *user) {
    std::string full_name_topic;

    if (Topic[1][0] == '#') {
        Topic[1].erase(0, 1);
        for (size_t i = 0; i < channels.size(); i++) {
            if (channels[i].getChannelName() == Topic[1]) {
                if (Topic[2][0] == ':')
                {
                    Topic[2].erase(0, 1);
                    for (size_t j = 2; j < Topic.size(); j++)
                        full_name_topic += Topic[j];
                    if (full_name_topic.empty())
                    {
                        sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), Topic[1], ""));
                        channels[i].set_topic("");
                    }
                    else
                    {
                        sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), Topic[1], full_name_topic));
                        channels[i].set_topic(full_name_topic);
                    }
                }
                else
                {
                    sendToClient(user->get_fd(), RPL_NOTOPIC(user->get_hostname(), Topic[1]));
                    std::cout << "Error: No topic (syntax `:`)" << std::endl;
                }
                return;
            }
        }
    }
    else {
        std::cout << "Error: No such channel (syntax `#`)"<< std::endl;
        // sendToClient(get_connect_client(atoi(Topic[0].c_str()))->get_fd(), REPLY_NOTONCHANNEL(Topic[1]));
    }
}

std::string Channels::get_topic() {
    return (topic);
}

void Server::DisplayTopic(std::string channel_name, Client *user) {
    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i].getChannelName() == channel_name) {
            if (channels[i].get_topic().empty())
                sendToClient(user->get_fd(), RPL_NOTOPIC(user->get_hostname(), channel_name));
            else
                sendToClient(user->get_fd(), RPL_TOPIC(user->get_hostname(), channel_name, channels[i].get_topic()));
        }
    }
    sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), channel_name, user->get_nickname()));
}

// TOPIC::TOPIC() {
//     _topic_name = "default";
// }

// TOPIC::TOPIC(const TOPIC &src) {
//     *this = src;
// }

// TOPIC &TOPIC::operator=(const TOPIC &src) {
//     _topic_name = src._topic_name;
//     return *this;
// }

// void TOPIC::addTopic(std::string topic) {
//     _topic_name = topic;
// }

// void TOPIC::removeTopic(std::string topic) {
//     _topic_name = topic;
// }

// void TOPIC::displayTopic() {
//     std::cout << "Topic: " << _topic_name << std::endl;
// }

// void TOPIC::displayMessage(std::string topic, std::string message) {
//     std::cout << "Topic: " << topic << std::endl;
//     std::cout << "Message: " << message << std::endl;
// }

// TOPIC::~TOPIC() {
// }
