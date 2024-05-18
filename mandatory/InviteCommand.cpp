#include  "../include/server.hpp"

void Server::InviteConstruction(Client *client)
{
    std::vector<std::string> vec = client->get_commande();

    // std::cout<<"****************************"<< std::endl;
    // for(size_t i = 0; i < vec.size(); i++)
    //     std::cout << "vec: " << vec[i]<< std::endl;
    // std::cout<< "****************************" << std::endl;

    // if (vec.size() < 3 || vec[1].empty() || !vec[1][1])
    // {
    //     std::string msg = ERROR_NEEDMOREPARAMSOR(client->get_nickname());
    //     if (send(client->get_fd(),msg.c_str(), msg.length(), 0) == -1)
    //         throw std::runtime_error("Failed Send JOIN message to the client");
    //     return ;
    // }
}