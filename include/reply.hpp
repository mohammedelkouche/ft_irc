/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:05:25 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/08/14 18:51:33 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	REPLY_HPP
#define REPLY_HPP

#include <iostream>
#include "./channels.hpp"
#include "./server.hpp"
#include <iostream>
#include "global.hpp"


#define REPLY_WELCOME(nick, hostname) ":" + hostname + " 001 " + nick + " :Welcome " + nick + " to the ft_irc network !\r\n"
#define REPLY_YOURHOST(nick, hostname) ":" + hostname + " 002 " + nick + " :Your host is " + hostname + " running version 1.0 !\r\n"
#define REPLY_CREATED(nick, hostname, formatted_time) ":" + hostname + " 003 " + nick + " :This server was created " + formatted_time + " !\r\n"
#define REPLY_MYINFO(nick, hostname) ":" + hostname + " 004 " + nick + " :Host: " + hostname + ", Version: 1.0, User mode: none, Channel modes: o, t, k, i !\r\n"

#define ERROR_PASSWDMISMATCH(nick, hostname) ":" + hostname + " 464 " + nick + " :Password incorrect !\r\n"
#define ERROR_ALREADYREGISTERED(nick, hostname) ":" + hostname + " 462 " + nick + " :You are already registered !\r\n"
#define ERROR_NOTREGISTERED(nick, hostname) ":" + hostname + " 451 " + nick + " :You have not registered !\r\n"

#define ERROR_ERRONEUSNICKNAME(nick, hostname) ":" + hostname + " 432 " + nick + " :Erroneus nickname !\r\n"
#define ERROR_NONICKNAMEGIVEN(nick, hostname) ":" + hostname + " 431 " + nick + " :No nickname given !\r\n"
#define ERROR_NICKNAMEINUSE(nick, hostname) ":" + hostname + " 433 " + nick + " :Nickname is already in use !\r\n"
#define REPLY_NICKCHANGE(oldNick, nick, hostname) ":" + oldNick + " NICK " + nick + "\r\n"

// #define ERROR_NEEDMOREPARAMSOR(nick)  (std::string (":") + " 461 " + nick + std::string(" :Not enough parameters !\r\n"))
#define ERROR_NEEDMOREPARAMS(nick, hostname) (std::string (":") + hostname + std::string(" 461 ") + nick + " :Not enough parameters !\r\n")
// #define ERROR_NEEDMOREPARAMSTOPIC(nick, hostname, command) (std::string (":") + hostname + std::string(" 461 ") + nick + std::string(" ") + command + " :Not enough parameters !\r\n")

#define PART_REPLY(nickname, username, hostname, channel) ":" + std::string(nickname) + "!~" + std::string(username) + "@" + std::string(hostname) + " PART " + std::string(channel) + "\r\n"

#define RPL_AWAY(sender , username, hostname, message , nick_resever) ":" + std::string(sender) + "!~" + std::string(username) + "@" + std::string(hostname) + " PRIVMSG " + nick_resever + " :" + message + "\r\n"

#define ERROR_BADCHANNELNAME(nick, hostname, channelname) ":" + hostname + " 476 " + nick + " " + channelname + " :Invalid channel name." + "\r\n"
#define ERROR_CHANNELISFULL(nick, channelName) (std::string(":") + nick + " 471 " + channelName + " :Cannot join channel (+l)\r\n")
#define ERROR_BADCHANNELKEY(nick, hostname, channelName) (std::string(":") + hostname + " 475 " + nick + " " + channelName + " :Cannot join channel (+K) - bad key\r\n")
#define ERROR_INVITEONLY(nick, channelName) ":" + nick + " 473 " + channelName + " :Cannot join channel (+i)\r\n"

#define REPLY_JOIN(nick, username, channelname, ipaddress) ":" + nick + "!~" + username + "@" + ipaddress + " JOIN " + channelname + "\r\n"
#define REPLY_TOPICDISPLAY(hostname, nick, channel, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
#define REPLY_TOPIC(hostname, nick, channel, setter, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + setter + " has set a new topic: " + topic + "\r\n"

#define REPLY_TOPICWHOTIME(topicsetter, time, nick, hostname, channelName) ":" + hostname + " 333 " + nick + " " + channelName + " " + topicsetter + "!~" + topicsetter + "@" + hostname + " " + time + "\r\n"
#define REPLY_NAMREPLY(hostname, clients, channelname, nick) ":" + hostname + " 353 " + nick + " = " + channelname + " :" + clients + "\r\n"
#define REPLY_ENDOFNAMES(hostname, nick, channelname) ":" + hostname + " 366 " + nick + " " + channelname + " :END of /NAMES list\r\n"

#define REPLY_MODEIS(channel, hostname, mode) ":" + hostname + " MODE " + channel + " " + mode + "\r\n"
#define REPLY_MODEISLIMIT(channel, hostname, mode, newlimit) ":" + hostname + " MODE " + channel + " " + mode + " " + newlimit + "\r\n"
#define REPLY_MODEISOP(channel, hostname, mode, target) ":" + hostname + " MODE " + channel + " " + mode + " " + target + "\r\n"
#define ERROR_INVALIDMODEPARAM(channel, hostname, flag) ":" + hostname + " 696 " + channel + " " + flag + " * you must specifiy a parameter for the op mode\r\n"
#define ERROR_USERNOTINCHANNEL(hostname, channel) ":" + hostname + " 441 " + channel + " " + ":they aren't on that channel\r\n"
#define ERROR_NOPRIVILEGES(hostname, channel) ":" + hostname + " 482 " + channel + " " + ":You're not a channel operator\r\n"

#define REPLY_CREATIONTIME(hostname, channelName, nick, time) ":" + hostname + " 329 " + nick + " " + channelName + " " + time + "\r\n"
#define REPLY_CHANNELMODES(hostname, channelName, nick, channelmode) ":" + hostname + " 324 " + nick + " " + channelName + " " + channelmode + "\r\n"

#define REPLY_INVITING(hostname, inviting, invited, channel) ":" + hostname + " 341 " + inviting + " " + invited + " " + channel + " :Inviting " + invited + " to " + channel + "\r\n"
#define REPLY_INVITE(nick, username, clienthostname, invited, channel) ":" + nick + "!" + username + "@" + clienthostname + " INVITE " + invited + " :" + channel + "\r\n"
#define ERROR_NOTONCHANNEL(hostname, channel) ":" + hostname + " 442 " + channel + " " + ":You're not on that channel\r\n"
#define ERROR_NOSUCHCHANNEL(hostname, channel, nick) ":" + hostname + " 403 " + nick + " " + channel + " :No such channel\r\n"
#define ERROR_NOSUCHNICK(hostname, channel, argument) ":" + hostname + " 401 " + channel + " " + argument + " :No such nickname\r\n"
#define ERROR_USERONCHANNEL(hostname, channel, nick) ":" + hostname + " 443 " + nick + " " + channel + "  :is already on channel\r\n"

#define ERROR_INPUTTOOLONG(nick, hostname) ":" + hostname + " 417 " + nick + " :Input line was too long !\r\n"

#define REPLY_VIEWTOPIC(hostname, nick, channel, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
#define REPLY_VIEWTIME(hostname, nick, channel, time) ":" + hostname + " 333 " + nick + " " + channel + " " + nick + " " + time + "\r\n"
#define REPLY_SETTOPIC(nick, hostname, channel, topic) ":" + nick + "!" + nick + "@" + hostname + " TOPIC " + channel + " :" + topic + "\r\n"

#define REPLY_BOT(hostname, nick, message) ":" + hostname + " 001 " + nick + " Dad joke: " + message + "\r\n"
#define ERROR_BOT(hostname, nick) ":" + hostname + " 450 " + nick + "enter [BOT generate] to generate a joke" + "\r\n"
#define REPLY_UMODEIS(hostname, channelname) ":" + hostname + " MODE " + channelname + " +nt\r\n"

#define ERROR_UNKNOWNMODE(nick, hostname, channel, character) ":" + hostname + " 472 " + nick + " " + channel + " " + character + " :is unknown mode char to me\r\n"
#define REPLY_YOUREOPER(hostname, nick) ":" + hostname + " 381 " + nick + ":You are now an IRC operator\r\n"
#define REPLY_KICK(kicker, username, host, channel, targetuser, reason) ":" + kicker + "!" + username + "@" + host + " KICK " + channel + " " + targetuser + " :" + reason + "\r\n"
#define PRIVMSG_FORMAT(senderNick, senderUsername, senderHostname, receiver, message) ":" + senderNick + "!~" + senderUsername + "@" + senderHostname + " PRIVMSG " + receiver + " :" + message + "\r\n"
#define ERROR_UNKNOWNCOMMAND(nick, hostname, command) ":" + hostname + " 421 " + nick + " " + command + " :Unknown command\r\n"


#define ERROR_UNKNOWNMODE(nick, hostname, channel, character) ":" + hostname + " 472 " + nick + " " + channel + " " + character + " :is unknown mode char to me\r\n"
#define REPLY_YOUREOPER(hostname, nick) ":" + hostname + " 381 " + nick + ":You are now an IRC operator\r\n"
#define REPLY_KICK(kicker, username, host, channel, targetuser, reason) ":" + kicker + "!" + username + "@" + host + " KICK " + channel + " " + targetuser + " :" + reason + "\r\n"
#define PRIVMSG_FORMAT(senderNick, senderUsername, senderHostname, receiver, message) ":" + senderNick + "!~" + senderUsername + "@" + senderHostname + " PRIVMSG " + receiver + " :" + message + "\r\n"
#define ERROR_UNKNOWNCOMMAND(nick, hostname, command) ":" + hostname + " 421 " + nick + " " + command + " :Unknown command\r\n"

#define RPL_NOTOPIC(hostname, channel) ":" + hostname + " 331 " + channel + " :No topic is set\r\n"
#define RPL_TOPIC(hostname, channel, topic) ":" + hostname + " 332 " + channel + " :" + topic + "\r\n"
#define ERR_NOTONCHANNEL(hostname, channel, nick) ":" + hostname + " 442 " + nick + " " + channel + " :You're not on that channel\r\n"
// #define RPL_AWAY(nick_resever, hostname, message) ":" + hostname +  " " + nick_resever + " :" + message + "\r\n"
#define ERR_NOTEXTTOSEND(hostname) ":" + hostname + " 412 " + ":No text to send\r\n"
#define ERR_NOSUCHNICK(hostname, nick) ":" + hostname + " 401 " + nick + " :No such nick\r\n"


// void	ERR_NEEDMOREPARAMS(std::string nick_name, std::string commande)
// {
// 	std::cout << "461 " <<  nick_name << " " << commande <<  " : Not enough parameters" << std::endl;
// }

#endif