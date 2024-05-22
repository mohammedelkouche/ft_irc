/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:10 by azgaoua           #+#    #+#             */
/*   Updated: 2024/05/22 06:04:50 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP
# define TOPIC_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>


class TOPIC {
    private:
        std::string     _topic_name;

    public:
        TOPIC           ();
        ~TOPIC          ();
        TOPIC           (const TOPIC &src);
        TOPIC           &operator=(const TOPIC &src);
        void            addTopic(std::string topic);
        void            removeTopic(std::string topic);
        void            displayTopic();
        void            displayMessage(std::string topic, std::string message);
};


#endif