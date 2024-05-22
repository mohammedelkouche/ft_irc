/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:03:45 by azgaoua           #+#    #+#             */
/*   Updated: 2024/05/22 06:05:10 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/topic.hpp"


TOPIC::TOPIC() {
    _topic_name = "default";
}

TOPIC::TOPIC(const TOPIC &src) {
    *this = src;
}

TOPIC &TOPIC::operator=(const TOPIC &src) {
    _topic_name = src._topic_name;
    return *this;
}

void TOPIC::addTopic(std::string topic) {
    _topic_name = topic;
}

void TOPIC::removeTopic(std::string topic) {
    _topic_name = topic;
}

void TOPIC::displayTopic() {
    std::cout << "Topic: " << _topic_name << std::endl;
}

void TOPIC::displayMessage(std::string topic, std::string message) {
    std::cout << "Topic: " << topic << std::endl;
    std::cout << "Message: " << message << std::endl;
}

TOPIC::~TOPIC() {
}
