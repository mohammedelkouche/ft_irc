// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <unistd.h>
// #include <sstream>
// #include <stdexcept>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <fcntl.h>
// #include <algorithm>


// #define BUFFER_SIZE 1024

// class Server 
// {
//     private :
//         int port;
//         std::string  pass;
//         int fd_s_socket;
//         std::vector<int> fd_client_sock;
//         std::vector<struct pollfd> fds;// fds clients
//         char buffer[BUFFER_SIZE];
//     public :
//         Server();
//         void config_server(int port, std::string password);
//         void accept_connection();
//         ~Server();
// };

// Server::Server()
// {}

// void    Server::config_server(int port, std::string password)
// {
//     this->port = port;
//     this->pass = password;

//     struct sockaddr_in server_addr;
//     this->fd_s_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (fd_s_socket == -1)
//         throw "socket creation error";

//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(this->port);
//     server_addr.sin_addr.s_addr = INADDR_ANY;

//     if (bind(fd_s_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
//          throw "binding error";
//     if (listen (fd_s_socket, SOMAXCONN) == -1)
//         throw "listening error";

//     // Set server socket to non-blocking
//     fcntl(fd_s_socket,F_SETFL, O_NONBLOCK);
// }
// Server::~Server()
// {}

// void    Server::accept_connection()
// {
//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);
//     int fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
//     if (fd_c_socket != -1) {
//         // Connection accepted successfully
//         // Set client socket to non-blocking
//         fcntl(fd_c_socket, F_SETFL, O_NONBLOCK);
//         fd_client_sock.push_back(fd_c_socket);
//         std::cout << "New client connected. fd: " << fd_c_socket << std::endl;
//     }
// }

// int main(int argc, char **argv)
// {
//     try
//     {
//         Server irc;
//         int port = std::atoi(argv[1]);
//         std::string pass = argv[2];
//         irc.config_server(port, pass);
//         std::cout << "Server started. Listening on port " << port << std::endl;
//         while(true)
//         {
//             irc.accept_connection();
//         }
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    
// }





///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdexcept>

class Client {
private:
    int fd;
    std::string ipAddress;
public:
    Client() {}
    // int GetFd() { return fd; }
    // void SetFd(int socketFd) { fd = socketFd; }
    void SetIpAddress(std::string ip) { ipAddress = ip; }
};

class Server {
private:
    int port;
    int serverSocketFd;
    std::vector<Client> clients;
    std::vector<struct pollfd> pollFds;
public:
    Server() { serverSocketFd = -1; }
    void InitializeServer();
    void CreateServerSocket();
    void AcceptNewClient();
    void ReceiveClientData(int fd);
    void CloseConnections();
    void RemoveClient(int fd);
};

void Server::RemoveClient(int fd) {
    for (size_t i = 0; i < pollFds.size(); i++) {
        if (pollFds[i].fd == fd) {
            pollFds.erase(pollFds.begin() + i);
            break;
        }
    }
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].GetFd() == fd) {
            clients.erase(clients.begin() + i);
            break;
        }
    }
}

void Server::CloseConnections() {
    for (size_t i = 0; i < clients.size(); i++) {
        std::cout << "Client <" << clients[i].GetFd() << "> Disconnected" << std::endl;
        close(clients[i].GetFd());
    }
    if (serverSocketFd != -1) {
        std::cout << "Server <" << serverSocketFd << "> Disconnected" << std::endl;
        close(serverSocketFd);
    }
}

void Server::ReceiveClientData(int fd) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesReceived = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
        std::cout << "Client <" << fd << "> Disconnected" << std::endl;
        RemoveClient(fd);
        close(fd);
    } else {
        buffer[bytesReceived] = '\0';
        std::cout << "Client <" << fd << "> Data: " << buffer;
    }
}

void Server::AcceptNewClient() {
    Client newClient;
    struct sockaddr_in clientAddress;
    socklen_t addressLength = sizeof(clientAddress);

    int incomingSocketFd = accept(serverSocketFd, (sockaddr *)&clientAddress, &addressLength);
    if (incomingSocketFd == -1) {
        std::cout << "accept() failed" << std::endl;
        return;
    }

    if (fcntl(incomingSocketFd, F_SETFL, O_NONBLOCK) == -1) {
        std::cout << "fcntl() failed" << std::endl;
        return;
    }

    struct pollfd newPollFd;
    newPollFd.fd = incomingSocketFd;
    newPollFd.events = POLLIN;
    newPollFd.revents = 0;

    newClient.SetFd(incomingSocketFd);
    newClient.SetIpAddress(inet_ntoa(clientAddress.sin_addr));
    clients.push_back(newClient);
    pollFds.push_back(newPollFd);

    std::cout << "Client <" << incomingSocketFd << "> Connected" << std::endl;
}

void Server::CreateServerSocket() {
    int enable = 1;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->port);

    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFd == -1)
        throw(std::runtime_error("Failed to create socket"));

    if (setsockopt(serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
        throw(std::runtime_error("Failed to set option (SO_REUSEADDR) on socket"));
    if (fcntl(serverSocketFd, F_SETFL, O_NONBLOCK) == -1)
        throw(std::runtime_error("Failed to set option (O_NONBLOCK) on socket"));
    if (bind(serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        throw(std::runtime_error("Failed to bind socket"));
    if (listen(serverSocketFd, SOMAXCONN) == -1)
        throw(std::runtime_error("listen() failed"));

    struct pollfd serverPollFd;
    serverPollFd.fd = serverSocketFd;
    serverPollFd.events = POLLIN;
    serverPollFd.revents = 0;
    pollFds.push_back(serverPollFd);
}

void Server::InitializeServer() {
    this->port = 1234;
    CreateServerSocket();

    std::cout << "Server <" << serverSocketFd << "> Connected" << std::endl;
    std::cout << "Waiting to accept a connection...\n";

    while (true) {
        if (poll(&pollFds[0], pollFds.size(), -1) == -1)
            throw(std::runtime_error("poll() failed"));

        for (size_t i = 0; i < pollFds.size(); i++) {
            if (pollFds[i].revents & POLLIN) {
                if (pollFds[i].fd == serverSocketFd)
                    AcceptNewClient();
                else
                    ReceiveClientData(pollFds[i].fd);
            }
        }
    }
}

int main() {
    Server server;
    std::cout << "---- SERVER ----" << std::endl;
    try {
        server.InitializeServer();
    } catch (const std::exception &e) {
        server.CloseConnections();
        std::cerr << e.what() << std::endl;
    }
    std::cout << "The Server Closed!" << std::endl;
    return 0;
}
