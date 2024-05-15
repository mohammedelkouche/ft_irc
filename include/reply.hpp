/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:05:25 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/15 16:43:01 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/server.hpp"
// #include "../include/client.hpp"

#ifndef	REPLY_HPP
#define REPLY_HPP

#include <iostream>
#include "./server.hpp"

// for password
// void	ERR_NEEDMOREPARAMS(std::string nick_name, std::string commande, int fd)
// {
// 	(void)fd;
// 	std::string errorMessage =  "461 " +  nick_name + " " + commande +  " : Not enough parameters";
// 	// sendToClient(fd, errorMessage);
// }
// void	ERR_PASSWDMISMATCH(std::string nick_name, std::string commande, int fd)
// {
// 	(void)fd;
// 	std::string errorMessage =  "464 " +  nick_name + " " + commande +  " :Password incorrect";
// 	// sendToClient(fd, errorMessage);
// }

// void	ERR_ALREADYREGISTERED(std::string nick_name, std::string commande, int fd)
// {
// 	(void)fd;
// 	std::string errorMessage = "462 " +  nick_name + " " + commande +  " :You may not reregister";
// 	// sendToClient(fd, errorMessage);
// }

// void	ERR_NICKNAMEINUSE(std::string nick_name, std::string commande, int fd)
// {
// 	(void)fd;
// 	std::string errorMessage = "432 " +  nick_name + " " + commande +  " :Nickname is already in use";
// 	// sendToClient(fd, errorMessage);
// }

// void	ERR_NOTREGISTERED(std::string nick_name, std::string commande, int fd)
// {
// 	(void)fd;
// 	std::string errorMessage = "451 " +  nick_name + " " + commande +  " :You have not registered";
// 	// sendToClient(fd, errorMessage);
// }

// void	ERR_NONICKNAMEGIVEN(std::string nick_name, int fd)
// {
// 	(void)fd;
// 	std::string errorMessage = "431 " +  nick_name + " " +  " :No nickname given";
// 	// sendToClient(fd, errorMessage);
// }



//--------------------- we have to work whith this macro ------------------------

// #define RPL_WELCOME(nick, hostname) ":" + hostname + " 001 " + nick + " :Welcome " + nick + " to the ft_irc network !\r\n"
// #define RPL_YOURHOST(nick, hostname) ":" + hostname + " 002 " + nick + " :Your host is " + hostname + " running version 1.0 !\r\n"
// #define RPL_CREATED(nick, hostname) ":" + hostname + " 003 " + nick + " :This server was created 2023-9-15 !\r\n"
// #define RPL_MYINFO(nick, hostname) ":" + hostname + " 004 " + nick + " :Host: " + hostname + ", Version: 1.0, User mode: none, Channel modes: o, t, k, i !\r\n"

#define ERROR_PASSWDMISMATCH(nick, hostname) ":" + hostname + " 464 " + nick + " :Password incorrect !\r\n"
#define ERROR_ALREADYREGISTERED(nick, hostname) ":" + hostname + " 462 " + nick + " :You may not reregister !\r\n"
#define ERROR_NEEDMOREPARAMS(nick, hostname) ":" + hostname + " 461 " + nick + " :Not enough parameters !\r\n"

#define ERROR_NOTREGISTERED(nick, hostname) ":" + hostname + " 451 " + nick + " :You have not registered !\r\n"
#define ERROR_NONICKNAMEGIVEN(nick, hostname) ":" + hostname + " 431 " + nick + " :No nickname given !\r\n"
#define ERROR_NICKNAMEINUSE(nick, hostname) ":" + hostname + " 433 " + nick + " :Nickname is already in use !\r\n"
#define ERROR_ERRONEUSNICKNAME(nick, hostname) ":" + hostname + " 432 " + nick + " :Erroneus nickname !\r\n"
#define REPLY_NICKCHANGE(oldnick, nick, hostname) ":" + oldnick + " NICK " + nick + "\r\n"


// #define ERR_BADCHANNELNAME(nick, hostname, channelname) ":" + hostname + " 476 " + nick + " " + channelname + " :Invalid channel name." + "\r\n"
// #define ERR_CHANNELISFULL(nick, channelName) ":" + nick + " 471 " + channelName + " :Cannot join channel (+l)\r\n"
// #define ERR_BADCHANNELKEY(nick, hostname, channelName) ":" + hostname + " 475 " + nick + " " + channelName + " :Cannot join channel (+K) - bad key\r\n"
// #define ERR_INVITEONLY(nick, channelName) ":" + nick + " 473 " + channelName + " :Cannot join channel (+i)\r\n"

// #define RPL_JOIN(nick, username, channelname, ipaddress) ":" + nick + "!~" + username + "@" + ipaddress + " JOIN " + channelname + "\r\n"
// #define RPL_TOPICDISPLAY(hostname, nick, channel, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
// #define RPL_TOPIC(hostname, nick, channel, setter, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + setter + " has set a new topic: " + topic + "\r\n"

// #define RPL_TOPICWHOTIME(topicsetter, time, nick, hostname, channelName) ":" + hostname + " 333 " + nick + " " + channelName + " " + topicsetter + "!~" + topicsetter + "@" + hostname + " " + time + "\r\n"
// #define RPL_NAMREPLY(hostname, clients, channelname, nick) ":" + hostname + " 353 " + nick + " = " + channelname + " :" + clients + "\r\n"
// #define RPL_ENDOFNAMES(hostname, nick, channelname) ":" + hostname + " 366 " + nick + " " + channelname + " :END of /NAMES list\r\n"

// #define RPL_MODEIS(channel, hostname, mode) ":" + hostname + " MODE " + channel + " " + mode + "\r\n"
// #define RPL_MODEISLIMIT(channel, hostname, mode, newlimit) ":" + hostname + " MODE " + channel + " " + mode + " " + newlimit + "\r\n"
// #define RPL_MODEISOP(channel, hostname, mode, target) ":" + hostname + " MODE " + channel + " " + mode + " " + target + "\r\n"
// #define ERR_INVALIDMODEPARAM(channel, hostname, flag) ":" + hostname + " 696 " + channel + " " + flag + " * you must specifiy a parameter for the op mode\r\n"
// #define ERR_USERNOTINCHANNEL(hostname, channel) ":" + hostname + " 441 " + channel + " " + ":they aren't on that channel\r\n"
// #define ERR_NOTOP(hostname, channel) ":" + hostname + " 482 " + channel + " " + ":You're not a channel operator\r\n"

// #define RPL_CREATIONTIME(hostname, channelName, nick, time) ":" + hostname + " 329 " + nick + " " + channelName + " " + time + "\r\n"
// #define RPL_CHANNELMODES(hostname, channelName, nick, channelmode) ":" + hostname + " 324 " + nick + " " + channelName + " " + channelmode + "\r\n"

// #define RPL_INVITING(hostname, inviting, invited, channel) ":" + hostname + " 341 " + inviting + " " + invited + " " + channel + " :Inviting " + invited + " to " + channel + "\r\n"
// #define RPL_INVITE(nick, username, clienthostname, invited, channel) ":" + nick + "!" + username + "@" + clienthostname + " INVITE " + invited + " :" + channel + "\r\n"
// #define ERR_NOTONCHANNEL(hostname, channel) ":" + hostname + " 442 " + channel + " " + ":You're not on that channel\r\n"
// #define ERR_NOSUCHCHANNEL(hostname, channel, nick) ":" + hostname + " 403 " + nick + " " + channel + " :No such channel\r\n"
// #define ERR_NOSUCHNICK(hostname, channel, argument) ":" + hostname + " 401 " + channel + " " + argument + " :No such nick/channel\r\n"
// #define ERR_USERONCHANNEL(hostname, channel, nick) ":" + hostname + " 443 " + nick + " " + channel + "  :is already on channel\r\n"

// #define ERR_INPUTTOOLONG(nick, hostname) ":" + hostname + " 417 " + nick + " :Input line was too long !\r\n"

// #define RPL_VIEWTOPIC(hostname, nick, channel, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
// #define RPL_VIEWTIME(hostname, nick, channel, time) ":" + hostname + " 333 " + nick + " " + channel + " " + nick + " " + time + "\r\n"
// #define RPL_SETTOPIC(nick, hostname, channel, topic) ":" + nick + "!" + nick + "@" + hostname + " TOPIC " + channel + " :" + topic + "\r\n"

// #define RPL_BOT(hostname, nick, message) ":" + hostname + " 001 " + nick + " Dad joke: " + message + "\r\n"
// #define ERR_BOT(hostname, nick) ":" + hostname + " 450 " + nick + "enter [BOT generate] to generate a joke" + "\r\n"
// #define RPL_UMODEIS(hostname, channelname) ":" + hostname + " MODE " + channelname + " +nt\r\n"

// #define ERR_UNKNOWNMODE(nick, hostname, channel, character) ":" + hostname + " 472 " + nick + " " + channel + " " + character + " :is unknown mode char to me\r\n"
// #define RPL_YOUREOPER(hostname, nick) ":" + hostname + " 381 " + nick + ":You are now an IRC operator\r\n"
// #define RPL_KICK(kicker, username, host, channel, targetuser, reason) ":" + kicker + "!" + username + "@" + host + " KICK " + channel + " " + targetuser + " :" + reason + "\r\n"
// #define PRIVMSG_FORMAT(senderNick, senderUsername, senderHostname, receiver, message) ":" + senderNick + "!~" + senderUsername + "@" + senderHostname + " PRIVMSG " + receiver + " :" + message + "\r\n"
#define ERROR_UNKNOWNCOMMAND(nick, hostname, command) ":" + hostname + " 421 " + nick + " " + command + " :Unknown command hay\r\n"


#endif