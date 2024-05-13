#include "../include/JoinCommand.hpp"



void JoinConstruction(std::vector<std::string> cmd, int clientFd)
{
    (void) clientFd;
    std::cout << "cmd  : " << cmd[1] << std::endl;
    // std::cout << "cmd.size()  : " << cmd.size() << std::endl;
    if(cmd.size() < 3)
        throw std::runtime_error("JOIN command error: should have two parameters");

    Channels channelName(cmd[1]); //here i extract the channel name from the whole string;
    channelName.join(clientFd);
    std::cout<< "Client joined "<< cmd[1] << " successfully !" << std::endl;
}