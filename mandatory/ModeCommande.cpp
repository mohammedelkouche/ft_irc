#include "../include/server.hpp"
#include "../include/reply.hpp"
#include "../include/channels.hpp"


bool is_number(std::string str)
{
	size_t found = str.find_first_not_of("0123456789");
	if (found == std::string::npos && std::atol(str.c_str()) <= 9223372036854775807)
		return (true);
	return (false);
}

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
	return (mode_rtn);
}

void Channel::init_modes()
{
	mode = 0;
	i = false;
	k = false;
	t = true;
	l = false;
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
void	Channel::add_l(size_t limit)
{
	l = true;
	this->limit = limit;
}
void	Channel::add_o(std::string nick)
{
	std::cout << nick << " should have the +o on this channel" << std::endl;
}
void	Channel::add_t()
{
	t = true;
}

void	Channel::rm_i()
{
	i = false;
}
void	Channel::rm_k(std::string old_key)
{
	if (getChannelKey() == old_key)
		k = false;

}
void	Channel::rm_l()
{
	l = false;
	limit = -1;
}
void	Channel::rm_o(std::string nick)
{
	std::cout << "need to check the " << nick << std::endl;
}
void	Channel::rm_t()
{
	t = false;
}

void	Channel::set_mode(int mode_number)
{
	mode = mode_number;
}

void Server::ModeCommand(std::vector<std::string> command, Client *user)
{
	int sign = 0;
	size_t arg_for_mode = 3;     
	size_t	i_i;
	std::string ryl_mode_enable;
	std::string ryl_args_p;
	std::string ryl_mode_desable;
	std::string ryl_args_m;
	
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
					sendToClient(user->get_fd(), REPLY_CREATIONTIME(user->get_hostname(), (*it)->getChannelName(), user->get_nickname(), (*it)->getTheChannelTimeCreated()));
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
				std::string full_mode_add;
				for (size_t i = 0; i < command[2].size(); i++)
					full_mode_add += command[2][i];
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
					if (full_mode_add[i] == 'i' && sign == 1)
					{
						if ((*it)->get_i() == false)
						{
							(*it)->add_i();
							ryl_mode_enable += "i";
						}
					}
					else if (full_mode_add[i] == 'k' && sign == 1)
					{
						if ((*it)->get_k() == false && command.size() >= (arg_for_mode + 1))
						{
							ryl_args_p += command[arg_for_mode] +  " ";
							(*it)->add_k(command[arg_for_mode++]);
							ryl_mode_enable += "k";
						}
					}
					else if (full_mode_add[i] == 'o' && sign == 1)
					{
						if (command.size() >= (arg_for_mode + 1))
						{
							for (i_i = 0; i_i < clients.size(); i_i++)
							{
								if ((clients[i_i]).get_nickname() == command[arg_for_mode] || (clients[i_i]).get_nickname() == "@" + command[arg_for_mode])
									break;
							}
							if ((i_i) >= clients.size())
								sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), command[arg_for_mode]));
							else
							{
								for (std::vector<Client *>::iterator it_c = Clnts.begin(); it_c != Clnts.end(); ++it_c)
								{
									if (((*it_c)->get_nickname() == command[arg_for_mode] && (*it_c)->getIsOperatorStatus() == false) || \
											((*it_c)->get_nickname() == "@" + command[arg_for_mode] && (*it_c)->getIsOperatorStatus() == false))
									{
										(*it_c)->setOperatorStatus(true);
										ryl_args_p += command[arg_for_mode] + " ";
										ryl_mode_enable += "o";
										break ;
									}
									else if ((*it_c)->get_nickname() == command[arg_for_mode])
										break ;
									else if ((*it_c) == Clnts[Clnts.size() - 1])
										sendToClient(user->get_fd(), ERROR_USERNOTINCHANNEL(user->get_hostname(), (*it)->getChannelName()));
								}
							}
							arg_for_mode++;
						}
					}
					else if (full_mode_add[i] == 't' && sign == 1)
					{
						if ((*it)->get_t() == false)
						{
							(*it)->add_t();
							ryl_mode_enable += "t";
						}
					}
					else if (full_mode_add[i] == 'l' && sign == 1)
					{	
						if (command.size() >= (arg_for_mode + 1) && is_number(command[arg_for_mode]))
						{
							if ((*it)->getChannelLimitNum() != (size_t)std::atol(command[arg_for_mode].c_str()))
							{
								ryl_args_p += command[arg_for_mode] + " ";
								ryl_mode_enable += "l";
								(*it)->add_l(std::atol(command[arg_for_mode].c_str()));
							}
						}
						arg_for_mode++;
					}
					else if (full_mode_add[i] == 'i' && sign == -1)
					{
						if ((*it)->get_i() == true)
						{
							(*it)->rm_i();
							ryl_mode_desable += "i";
						}
					}
					else if (full_mode_add[i] == 'k' && sign == -1)
					{
						if ((*it)->get_k() == true)
						{
							(*it)->rm_k(command[arg_for_mode]);
							if ((*it)->get_k() == false)
							{
								ryl_args_m += "* ";
								ryl_mode_desable += "k";
							}
							else
								sendToClient(user->get_fd(), ERR_KEYSET(user->get_hostname(), (*it)->getChannelName()));
						}
						arg_for_mode++;
					}
					else if (full_mode_add[i] == 'o' && sign == -1)
					{
						if (command.size() >= (arg_for_mode + 1))
						{
							for (i_i = 0; i_i < clients.size(); i_i++)
							{
								if ((clients[i_i]).get_nickname() == command[arg_for_mode] || (clients[i_i]).get_nickname() == "@" + command[arg_for_mode])
									break;
							}
							if ((i_i) >= clients.size())
								sendToClient(user->get_fd(), ERR_NOSUCHNICK(user->get_hostname(), command[arg_for_mode]));
							else
							{
								for (std::vector<Client *>::iterator it_c = Clnts.begin(); it_c != Clnts.end(); ++it_c)
								{
									if (((*it_c)->get_nickname() == command[arg_for_mode] && (*it_c)->getIsOperatorStatus() == true) || \
										((*it_c)->get_nickname() == "@" + command[arg_for_mode] && (*it_c)->getIsOperatorStatus() == true))
									{
										(*it_c)->setOperatorStatus(false);
										ryl_mode_desable += "o";
										ryl_args_m += command[arg_for_mode] + " ";
										break ;
									}
									else if ((*it_c)->get_nickname() == command[arg_for_mode])
										break ;
									else if ((*it_c) == Clnts[Clnts.size() - 1])
										sendToClient(user->get_fd(), ERROR_USERNOTINCHANNEL(user->get_hostname(), (*it)->getChannelName()));
								}
							}
							arg_for_mode++;
						}
					}
					else if (full_mode_add[i] == 't' && sign == -1)
					{
						if ((*it)->get_t() == true)
						{
							(*it)->rm_t();
							ryl_mode_desable += "t";
						}
					}
					else if (full_mode_add[i] == 'l' && sign == -1)
					{	
						if ((*it)->get_l() == true)
						{
							(*it)->rm_l();
						}
						ryl_mode_desable += "l";
					}
					else if (full_mode_add[i] != 'l' && full_mode_add[i] != 'i' && full_mode_add[i] != 't' && full_mode_add[i] != 'o' && full_mode_add[i] != 'k')
						sendToClient(user->get_fd(), ERR_UNKNOWNMODE(user->get_hostname(), user->get_nickname(), full_mode_add[i]));
				}
				std::string reply_mode;
				if (ryl_mode_enable.empty() == false)
				{
					reply_mode += "+" + ryl_mode_enable;
				}
				if (ryl_mode_desable.empty() == false)
				{
					reply_mode += "-" + ryl_mode_desable;
				}
				if (ryl_args_p.empty() == false)
				{
					reply_mode += " " + ryl_args_p;
					reply_mode.erase(reply_mode.size() - 1, 1);
				}
				if (ryl_args_m.empty() == false)
				{
					reply_mode += " " + ryl_args_m;
					reply_mode.erase(reply_mode.size() - 1, 1);
				}
				if (reply_mode.empty() == false)
				{
					sendToChannel(user, REPLY_CHANNELMODES__(user->get_username(), (*it)->getChannelName(), user->get_nickname(), reply_mode), (*it)->getChannelName());
					sendToClient(user->get_fd(), REPLY_CHANNELMODES__(user->get_username(), (*it)->getChannelName(), user->get_nickname(), reply_mode));
				}
				else if (command.size() <= 3)
				{
					sendToClient(user->get_fd(), REPLY_CHANNELMODES(user->get_hostname(), (*it)->getChannelName(), user->get_nickname(), (*it)->get_channel_mode()));
					sendToClient(user->get_fd(), REPLY_CREATIONTIME(user->get_hostname(), (*it)->getChannelName(), user->get_nickname(), (*it)->getTheChannelTimeCreated()));
				}
				std::cout << "limit is ->> :" << (*it)->getChannelLimitNum() << std::endl;
				return ;
			}
		}
		sendToClient(user->get_fd(), ERR_NOTONCHANNEL(user->get_hostname(), command[1], user->get_nickname()));
	}
	else
        sendToClient(user->get_fd(), ERROR_NOSUCHCHANNEL(user->get_hostname(), \
                            command[1], user->get_nickname()));
}
