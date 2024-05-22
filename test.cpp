// #include <iostream>
// #include <sstream>

// int main ()
// {
//     std::string s = "hello";
//     std::string s1 = "\t";
//     std::string s2 = "world";
//     std::stringstream ss(s + s1 + s2);

//     for (int i = 0; i < 2; i++)
//     {

//     ss >> s;
//     std::cout << s << std::endl;
//     }
// }


/////////////////////////////////

// #include <iostream>
// #include <ctime>

// void displayServerCreationTime() {
//     // Get the current time
//     std::time_t currentTime = std::time(NULL);

//     // Convert to UTC time
//     std::tm* utcTime = std::gmtime(&currentTime);

//     // Buffer to hold the formatted date and time string
//     char buffer[80];

//     // Format the date and time according to the specified format
//     std::strftime(buffer, sizeof(buffer), "This server was created %a, %d %b %Y %H:%M:%S %Z", utcTime);

//     // Display the formatted date and time string
//     std::cout << buffer << std::endl;
// }

// int main() {
//     displayServerCreationTime();
//     return 0;
// }



// std::string getServerCreationTime() {
//     std::time_t currentTime = std::time(NULL);
//     std::tm* utcTime = std::gmtime(&currentTime);
//     char buffer[80];
//     std::strftime(buffer, sizeof(buffer), "This server was created %a, %d %b %Y %H:%M:%S %Z", utcTime);
//     return std::string(buffer);
// }



///////////////////////////////


// #include <iostream>
// #include <ctime>
// #include <string>
// #include <sys/socket.h>
// #include <unistd.h> // for close()

// // Function to send data to a client identified by its file descriptor
// void sendToClient(int fd, const std::string &message) {
//     send(fd, message.c_str(), message.length(), 0);
// }

// // Function to get the formatted server creation time message
// std::string getServerCreationTime() {
//     // Get the current time
//     std::time_t currentTime = std::time(NULL);

//     // Convert to UTC time
//     std::tm* utcTime = std::gmtime(&currentTime);

//     // Buffer to hold the formatted date and time string
//     char buffer[80];

//     // Format the date and time according to the specified format
//     std::strftime(buffer, sizeof(buffer), "This server was created %a, %d %b %Y %H:%M:%S %Z", utcTime);

//     // Return the formatted date and time string as a std::string
//     return std::string(buffer);
// }

// int main() {
//     // Example file descriptor, replace with actual client's file descriptor
//     int client_fd = 1; // STDOUT for demonstration, use actual client FD in real usage

//     // Get the server creation time message
//     std::string message = getServerCreationTime();

//     // Send the message to the client
//     sendToClient(client_fd, message);

//     return 0;
// }


///////////////////////



// #include <iostream>
// #include <ctime>
// #include <string>
// #include <sys/socket.h>
// #include <unistd.h> // for close()

// // Macro to generate the creation message
// #define RPL_CREATED(nick, hostname, formatted_time) ":" + hostname + " 003 " + nick + " :This server was created " + formatted_time + " !\r\n"

// // Function to send data to a client identified by its file descriptor
// void sendToClient(int fd, const std::string &message) {
//     send(fd, message.c_str(), message.length(), 0);
// }

// // Function to get the formatted server creation time
// std::string getFormattedTime() {
//     // Get the current time
//     std::time_t currentTime = std::time(NULL);

//     // Convert to UTC time
//     std::tm* utcTime = std::gmtime(&currentTime);

//     // Buffer to hold the formatted date and time string
//     char buffer[80];

//     // Format the date and time according to the specified format
//     std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", utcTime);

//     // Return the formatted date and time string as a std::string
//     return std::string(buffer);
// }

// int main() {
//     // Example file descriptor, replace with actual client's file descriptor
//     int client_fd = 1; // STDOUT for demonstration, use actual client FD in real usage

//     // Example nick and hostname
//     std::string nick = "nickname";
//     std::string hostname = "hostname";

//     // Get the formatted time string
//     std::string formatted_time = getFormattedTime();

//     // Generate the message using the macro
//     std::string message = RPL_CREATED(nick, hostname, formatted_time);

//     // Send the message to the client
//     sendToClient(client_fd, message);

//     return 0;
// }

// #define REPLY_CREATED(nick, hostname, formatted_time) ":" + hostname + " 003 " + nick + " :This server was created " + formatted_time + " !\r\n"



// int main() {
//     Client user;
//     user.set_fd(1); // STDOUT for demonstration, use actual client FD in real usage
//     user.set_nickname("nickname");
//     user.set_hostname("hostname");

//     std::string formatted_time = getFormattedTime();
    
//     sendToClient(user.get_fd(), REPLY_CREATED(user.get_nickname(), user.get_hostname(), formatted_time));

//     return 0;
// }






// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm> // for std::find

// int main() {
//     std::vector<std::string> commande;

//     // Adding elements to the vector
//     commande.push_back("test");
//     commande.push_back(":");
//     commande.push_back("hello");

//     // Find the element ":"
//      std::cout << "befor" << std::endl;
//     for (std::vector<std::string>::iterator iter = commande.begin(); iter != commande.end(); ++iter) {
//         std::cout << *iter << std::endl;
//     }
//     std::vector<std::string>::iterator it = std::find(commande.begin(), commande.end(), ":");
    
//     // Check if the element was found
//     if (it != commande.end()) {
//         // Erase the element
//         commande.erase(it);
//     }

//      std::cout << "after" << std::endl;
//     // Output the contents of the vector to verify the result
//     for (std::vector<std::string>::iterator iter = commande.begin(); iter != commande.end(); ++iter) {
//         std::cout << *iter << std::endl;
//     }

//     return 0;
// }
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const char *SERVER_IP = "127.0.0.1"; // Change to your server's IP
const int SERVER_PORT = 6667;        // Change to your server's port
const int BUFFER_SIZE = 512;

int connect_to_server(const char *server_ip, int server_port) {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported." << std::endl;
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        close(sockfd);
        return -1;
    }

    return sockfd;
}

void send_to_server(int sockfd, const std::string &message) {
    send(sockfd, message.c_str(), message.length(), 0);
}

std::string receive_from_server(int sockfd) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "Error receiving data." << std::endl;
    }
    return std::string(buffer);
}

int main() {
    int sockfd = connect_to_server(SERVER_IP, SERVER_PORT);
    if (sockfd < 0) {
        return 1;
    }

    // Register with the server
    std::string nick = "NICK testuser\r\n";
    std::string user = "USER testuser 0 * :Test User\r\n";

    send_to_server(sockfd, nick);
    send_to_server(sockfd, user);

    // Join a channel
    std::string join = "JOIN #testchannel\r\n";
    send_to_server(sockfd, join);

    // Send a message to the channel
    std::string message = "PRIVMSG #testchannel :Hello, World!\r\n";
    send_to_server(sockfd, message);

    // Receive and print responses from the server
    while (true) {
        std::string response = receive_from_server(sockfd);
        if (!response.empty()) {
            std::cout << response;
        }
    }

    close(sockfd);
    return 0;
}
