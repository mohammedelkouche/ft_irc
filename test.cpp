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



// ----------------------------



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

// ----------------------------


// #include <iostream>
// #include <cstdlib>
// #include <ctime>



// // time(NULL) returns the current time in seconds since the 
// // Epoch (usually January 1, 1970). This value changes every second.

// // By using time(NULL) as the seed, you ensure that the sequence of 
// // random numbers is different each time you run the program, 
// // because the seed will be based on the current time.



// int main() {
//     srand(time(NULL)); // Try commenting this line out to see the difference
//     for (int i = 0; i < 5; ++i) {
//         std::cout << rand() % 100 << std::endl; // Generate a random number between 0 and 99
//     }
//     return 0;
// }