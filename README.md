# OUSSAMA : JOIN - INVITE - KICK - PART

**send()**
>send() is a fundamental function for network communication in C and C++   programming, allowing data to be transmitted over network sockets between client  and server applications.  


**JOIN message**  
>Command: JOIN  
- Parameters: <channel>{,<channel>} [<key>{,<key>}]  
Alt Params: 0  
The JOIN command indicates that the client wants to join the given channel(s), each channel using the given key for it. The server receiving the command checks whether or not the client can join the given channel, and processes the request. Servers MUST process the parameters of this command as lists on incoming commands from clients, with the first <key> being used for the first <channel>, the second <key> being used for the second <channel>, etc.

>Command INVITE



>Command: PART

