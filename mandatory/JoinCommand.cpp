#include "../include/JoinCommand.hpp"

// bool isCorrectChannel(std::string channel)
// {
//     if (std::alphanum())
// }

void JoinConstruction(Client *client)
{
    // std::cout << "channel  : " << cmd[1] << std::endl;
    // std::cout << "cmd.size()  : " << cmd.size() << std::endl;
    // std::string serverMsg ;
    std::vector<std::string> cmd = client->get_commande();
    std::string msg = ERR_BADCHANNELKEY(client->get_nickname(), "localhost" , cmd[1]);
    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1])
    {
        if (send(client->get_fd(),msg.c_str(), msg.length(), 0))
            return ;
        else
            throw std::runtime_error("Failed Send JOIN message to the client");
    }
    Channels channel(cmd[1]);
    channel.join(client->get_fd(), client);
    // std::cout<< "Client joined "<< cmd[1] << " successfully !" << std::endl;
}