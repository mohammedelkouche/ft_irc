#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
// #include <>

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
    

    return (0);
}