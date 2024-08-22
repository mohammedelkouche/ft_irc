#include "../include/server.hpp"
#include "../include/reply.hpp"
#include "../include/channels.hpp"


std::string Channel::get_channel_mode()
{
	std::string mode_rtn = "+";
	if (this->get_i() == true)
		mode_rtn += "i";
	if (this->get_k() == true)
		mode_rtn += "k";
	if (this->get_l() == true)
		mode_rtn += "l";
	if (this->get_t() == true)
		mode_rtn += "t";
	if (mode_rtn == "+")
		return ("no mode is set");
	return (mode_rtn);
}

void Channel::init_modes()
{
	mode = 0;
	i = false;
	k = false;
	o = false;
	t = false;
	l = false;
	key = "";
	limit = -1;
}

bool	Channel::get_i()
{
	return (i);
}
bool	Channel::get_k()
{
	return (k);
}
bool	Channel::get_l()
{
	return (l);
}
bool	Channel::get_o()
{
	return (o);
}
bool	Channel::get_t()
{
	return (t);
}


void	Channel::add_i()
{
	i = true;
}
void	Channel::add_k(std::string key)
{
	k = true;
	this->key = key;
}
void	Channel::add_l(int limit)
{
	l = true;
	this->limit = limit;
}
void	Channel::add_o(std::string nick)
{
	std::cout << nick << " should have the +o on this channel" << std::endl;
	o = true;
}
void	Channel::add_t()
{
	t = true;
}

void	Channel::rm_i()
{
	i = false;
}
void	Channel::rm_k(std::string key)
{
	if (this->key == key)
		k = false;
	else
		std::cout << "invalid key" << std::endl;
}
void	Channel::rm_l()
{
	l = false;
	limit = -1;
}
void	Channel::rm_o(std::string nick)
{
	std::cout << "need to check the " << nick << std::endl;
	o = false;
}
void	Channel::rm_t()
{
	t = false;
}

void	Channel::set_mode(int mode_number)
{
	mode = mode_number;
}

//ERROR_INVALIDMODEPARAM
//ERR_INVALIDKEY ******to do******

void Server::ModeCommand(std::vector<std::string> command, Client *user)
{
	int mode_number = 0;
	int sign = 0;
	size_t arg_for_mode = 3;
	size_t	i_i;

	if (command.size() == 1)
	{
		sendToClient(user->get_fd(), ERROR_NEEDMOREPARAMS(user->get_nickname(), \
                        user->get_hostname()));
		return ;
	}
	if (command[1][0] == '#')
	{
		if (no_suck_channel(command) == 1)
        {
            sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), \
                            command[1], user->get_nickname()));
            return ;
        }
		for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if ((*it)->getChannelName() == command[1])
            {
				if (command.size() == 2)
				{
					sendToClient(user->get_fd(), REPLY_CHANNELMODES(user->get_hostname(), (*it)->getChannelName(), user->get_nickname(), (*it)->get_channel_mode()));
					//need time of the creation of the channel for making the REPLY_CREATIONTIME
					return ;
				}
				std::vector<Client *> Clnts = (*it)->GetClientssHouse();
				if (on_channel(Clnts, user) == 0)
                    break ;
				for (std::vector<Client *>::iterator it = Clnts.begin(); it != Clnts.end(); ++it)
				{
					if ((*it)->get_nickname() == user->get_nickname())
					{
						if ((*it)->getIsOperatorStatus() == 0)
						{
							sendToClient(user->get_fd(), ERROR_NOPRIVILEGES(user->get_hostname(), command[1]));
							return ; 
						}
						else
							break;
					}
				}
				if (command[2][0] == '+' || command[2][0] == '-')
				{
					std::string full_mode_add;

					for (size_t i = 0; i < command[2].size(); i++)
						full_mode_add += command[2][i];
					std::cout << "this is full_mode -> " << full_mode_add << std::endl;
					for (size_t i = 0; i < full_mode_add.size(); i++)
					{
						if (full_mode_add[i] == '+' || full_mode_add[i] == '-')
						{
							while (full_mode_add[i] == '+' || full_mode_add[i] == '-')
							{
								while (full_mode_add[i] == '+')
								{
									sign = 1;
									i++;
								}
								while (full_mode_add[i] == '-')
								{
									sign = -1;
									i++;
								}
							}
						}
						if (sign == 0)
						{
							std::cout << "```the correct reply should send```\n" << "sign problem" << std::endl;
							return ;
						}
						if (full_mode_add[i] == 'i' && sign == 1)
						{
							if ((*it)->get_i() == false)
							{
								(*it)->add_i();
								mode_number += 1;
							}
						}
						else if (full_mode_add[i] == 'k' && sign == 1)
						{
							if ((*it)->get_k() == false && command.size() >= (arg_for_mode + 1))
							{
								(*it)->add_k(command[arg_for_mode++]);
								mode_number += 2;
							}
							else if (command.size() < (arg_for_mode + 1))
								sendToClient(user->get_fd(), ERROR_INVALIDMODEPARAM((*it)->getChannelName(), user->get_hostname(), full_mode_add[i]));
						}
						else if (full_mode_add[i] == 'o' && sign == 1)
						{
							if (command.size() >= (arg_for_mode + 1))
							{
								for (i_i = 0; i_i < clients.size(); i_i++)
								{
									if ((clients[i_i]).get_nickname() == command[arg_for_mode])
										break;
								}
								if ((i_i) >= clients.size())
									sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), command[arg_for_mode]));
								else
								{
									for (std::vector<Client *>::iterator it_c = Clnts.begin(); it_c != Clnts.end(); ++it_c)
									{
										if ((*it_c)->get_nickname() == command[arg_for_mode] && (*it_c)->getIsOperatorStatus() == false)
										{
											(*it_c)->setOperatorStatus(true);
											mode_number += 4;
										}
										else if ((*it_c)->get_nickname() == command[arg_for_mode])
											break ;
										else if ((*it_c) == Clnts[Clnts.size() - 1])
											sendToClient(user->get_fd(), ERROR_USERNOTINCHANNEL(user->get_hostname(), (*it)->getChannelName()));
									}
								}
								arg_for_mode++;
							}
							else
								sendToClient(user->get_fd(), ERROR_INVALIDMODEPARAM((*it)->getChannelName(), user->get_hostname(), full_mode_add[i]));
						}
						else if (full_mode_add[i] == 't' && sign == 1)
						{
							if ((*it)->get_t() == false)
							{
								(*it)->add_t();
								mode_number += 8;
							}
						}
						else if (full_mode_add[i] == 'l' && sign == 1)
						{	
							if (command.size() >= (arg_for_mode + 1))
							{
								(*it)->add_l(std::atoi(command[arg_for_mode].c_str()));
								sendToClient(user->get_fd(), REPLY_MODEISLIMIT(command[1], user->get_hostname(), "+l", command[arg_for_mode++]));
								mode_number += 16;
							}
							else
								sendToClient(user->get_fd(), ERROR_INVALIDMODEPARAM((*it)->getChannelName(), user->get_hostname(), full_mode_add[i]));
						}
						else if (full_mode_add[i] == 'i' && sign == -1)
						{
							if ((*it)->get_i() == true)
							{
								(*it)->rm_i();
								mode_number -= 1;
							}
						}
						else if (full_mode_add[i] == 'k' && sign == -1)
						{
							if ((*it)->get_k() == true && command.size() >= (arg_for_mode + 1))
							{
								(*it)->rm_k(command[arg_for_mode++]);
								mode_number -= 2;
							}
							else if (command.size() < (arg_for_mode + 1))
								sendToClient(user->get_fd(), ERROR_INVALIDMODEPARAM((*it)->getChannelName(), user->get_hostname(), full_mode_add[i]));
						}
						else if (full_mode_add[i] == 'o' && sign == -1)
						{
							if (command.size() >= (arg_for_mode + 1))
							{
								for (i_i = 0; i_i < clients.size(); i_i++)
								{
									if ((clients[i_i]).get_nickname() == command[arg_for_mode])
										break;
								}
								if ((i_i) >= clients.size())
									sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), command[arg_for_mode]));
								else
								{
									for (std::vector<Client *>::iterator it_c = Clnts.begin(); it_c != Clnts.end(); ++it_c)
									{
										if ((*it_c)->get_nickname() == command[arg_for_mode] && (*it_c)->getIsOperatorStatus() == true)
										{
											(*it_c)->setOperatorStatus(false);
											mode_number -= 4;
										}
										else if ((*it_c)->get_nickname() == command[arg_for_mode])
											break ;
										else if ((*it_c) == Clnts[Clnts.size() - 1])
											sendToClient(user->get_fd(), ERROR_USERNOTINCHANNEL(user->get_hostname(), (*it)->getChannelName()));
									}
								}
								arg_for_mode++;
							}
							else
								sendToClient(user->get_fd(), ERROR_INVALIDMODEPARAM((*it)->getChannelName(), user->get_hostname(), full_mode_add[i]));
						}
						else if (full_mode_add[i] == 't' && sign == -1)
						{
							if ((*it)->get_t() == true)
							{
								(*it)->rm_t();
								mode_number -= 8;
							}
						}
						else if (full_mode_add[i] == 'l' && sign == -1)
						{	
							if ((*it)->get_l() == true)
							{
								(*it)->rm_l();
								mode_number -= 16;
							}
						}
						else
							sendToClient(user->get_fd(), ERR_UNKNOWNMODE(user->get_hostname(), user->get_nickname(), full_mode_add[i]));
					}
					(*it)->set_mode(mode_number);
				}
				sendToChannel(user, REPLY_CHANNELMODES(user->get_hostname(), (*it)->getChannelName(), user->get_nickname(), (*it)->get_channel_mode()), (*it)->getChannelName());
				//need time of the creation of the channel for making the REPLY_CREATIONTIME	
				std::cout << "the mode is " << mode_number << std::endl;
				return ;
			}
		}
		sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), command[1], user->get_nickname()));
	}
	else
        sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), \
                            command[1], user->get_nickname()));
	// switch (mode_number) {
	// 	case 1:
	// 		add_i(user);
	// 	case 2:
	// 		add_k(user);
	// 	case 3:
	// 		add_i(user);
	// 		add_k(user);
	// 	case 4:
	// 		add_o(user);
	// 	case 5:
	// 		add_o(user);
	// 		add_i(user);
	// 	case 6:
	// 		add_k(user);
	// 		add_o(user);
	// 	case 7:
	// 		add_k(user);
	// 		add_o(user);
	// 		add_i(user);
	// 	case 8:
	// 		add_t(user);
	// 	case 9:
	// 		add_t(user);
	// 		add_i(user);
	// 	case 10:
	// 		add_t(user);
	// 		add_k(user);
	// 	case 11:
	// 		add_t(user);
	// 		add_k(user);
	// 		add_i(user);
	// 	case 12:
	// 		add_t(user);
	// 		add_o(user);
	// 	case 13:
	// 		add_i(user);
	// 		add_o(user);
	// 		add_t(user);
	// 	case 14:
	// 		add_t(user);
	// 		add_o(user);
	// 		add_k(user);
	// 	case 15:
	// 		add_i(user);
	// 		add_t(user);
	// 		add_o(user);
	// 		add_k(user);
	// 	case 16:
	// 		add_l(user);
	// 	case 17:
	// 		add_l(user);
	// 		add_i(user);
	// 	case 18:
	// 		add_l(user);
	// 		add_k(user);
	// 	case 19:
	// 		add_l(user);
	// 		add_i(user);
	// 		add_k(user);
	// 	case 20:
	// 		add_l(user);
	// 		add_o(user);
	// 	case 21:
	// 		add_l(user);
	// 		add_o(user);
	// 		add_i(user);
	// 	case 22:
	// 		add_k(user);
	// 		add_o(user);
	// 		add_l(user);
	// 	case 23:
	// 		add_k(user);
	// 		add_o(user);
	// 		add_l(user);
	// 		add_i(user);
	// 	case 24:
	// 		add_t(user);
	// 		add_l(user);
	// 	case 25:
	// 		add_t(user);
	// 		add_l(user);
	// 		add_i(user);
	// 	case 26:
	// 		add_l(user);
	// 		add_t(user);
	// 		add_k(user);
	// 	case 27:
	// 		add_l(user);
	// 		add_t(user);
	// 		add_k(user);
	// 		add_i(user);
	// 	case 28:
	// 		add_l(user);
	// 		add_o(user);
	// 		add_t(user);
	// 	case 29:
	// 		add_l(user);
	// 		add_o(user);
	// 		add_t(user);
	// 		add_i(user);
	// 	case 30:
	// 		add_l(user);
	// 		add_o(user);
	// 		add_k(user);
	// 		add_t(user);
	// 	case 31
	// 		add_l(user);
	// 		add_o(user);
	// 		add_k(user);
	// 		add_t(user);
	// 		add_i(user);
	// }
}
