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



#include <iostream>
#include <ctime>
#include <string>
#include <sys/socket.h>
#include <unistd.h> // for close()

// Macro to generate the creation message
#define RPL_CREATED(nick, hostname, formatted_time) ":" + hostname + " 003 " + nick + " :This server was created " + formatted_time + " !\r\n"

// Function to send data to a client identified by its file descriptor
void sendToClient(int fd, const std::string &message) {
    send(fd, message.c_str(), message.length(), 0);
}

// Function to get the formatted server creation time
std::string getFormattedTime() {
    // Get the current time
    std::time_t currentTime = std::time(NULL);

    // Convert to UTC time
    std::tm* utcTime = std::gmtime(&currentTime);

    // Buffer to hold the formatted date and time string
    char buffer[80];

    // Format the date and time according to the specified format
    std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", utcTime);

    // Return the formatted date and time string as a std::string
    return std::string(buffer);
}

int main() {
    // Example file descriptor, replace with actual client's file descriptor
    int client_fd = 1; // STDOUT for demonstration, use actual client FD in real usage

    // Example nick and hostname
    std::string nick = "nickname";
    std::string hostname = "hostname";

    // Get the formatted time string
    std::string formatted_time = getFormattedTime();

    // Generate the message using the macro
    std::string message = RPL_CREATED(nick, hostname, formatted_time);

    // Send the message to the client
    sendToClient(client_fd, message);

    return 0;
}

#define REPLY_CREATED(nick, hostname, formatted_time) ":" + hostname + " 003 " + nick + " :This server was created " + formatted_time + " !\r\n"



// int main() {
//     Client user;
//     user.set_fd(1); // STDOUT for demonstration, use actual client FD in real usage
//     user.set_nickname("nickname");
//     user.set_hostname("hostname");

//     std::string formatted_time = getFormattedTime();
    
//     sendToClient(user.get_fd(), REPLY_CREATED(user.get_nickname(), user.get_hostname(), formatted_time));

//     return 0;
// }