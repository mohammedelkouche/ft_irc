#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
// #include <>

const int PORT = 8080;
const int MAX_CLIENTS = 5;
const int BUFFER_SIZE = 1024;

int main(int argc, char **argv)
{
    // creat socket
    int serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket == -1)
    {
        std::cout << "Error could not creat socket \n";
        // std::cerr << "Error could not creat socket \n";
        return (1);
    }
    // bind the socket to an IP addres and port
    // sockaddr_in serverAddress;
    struct sockaddr_in serverAddress;

    return (0);
}