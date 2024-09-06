**send()**
>send() is a fundamental function for network communication in C and C++   programming, allowing data to be transmitted over network sockets between client  and server applications.  


**Channel commands**  
>Command: JOIN  
- Parameters: <channel>{,<channel>} [<key>{,<key>}]  
Alt Params: 0  
The JOIN command indicates that the client wants to join the given channel(s), each channel using the given key for it. The server receiving the command checks whether or not the client can join the given channel, and processes the request. Servers MUST process the parameters of this command as lists on incoming commands from clients, with the first <key> being used for the first <channel>, the second <key> being used for the second <channel>, etc.

>Command INVITE
    Parameters: <nickname> <channel>

>Command: PART
    Parameters: <channel>{,<channel>} [<reason>]

>Command: KICK  
    Parameters: <channel> <user> *( "," <user> ) [<comment>]  


# T9ABY VERIFIWHOM A CHABIBA  

>PASS:  
    PASS password  
  
>NICK:  
    NICK nickname // nickname must not contain spaces  
  
>USER:  
    USER name 0 * fullname  
  
>INVITE:  
    INVITE nickname #channel_name // [operator]: add nickname to invite list (no to the channel)  
  
>JOIN:  
    // if channel mode is +i: only invited users can join, else anyone can join  
    JOIN #channel_name                             // [ anyone]  
    JOIN #channel_name channel_paswword            // [ anyone]  
    JOIN ch1,ch2                                   // [ anyone]  
    JOIN ch1,ch2 pas1,pas2                         // [ anyone]  
    JOIN ch1,ch2,ch3 pas1,pas2 // ch3 without key  // [ anyone]  
  
>KICK:  
    KICK #channel_name nickname // [operator]  
  
>MODE:  
    MODE #channel_name                                     // [ anyone ]: display channel modes  
    MODE #channel_name +i                                  // [ operator] set channel mode to invite only   
    MODE #channel_name +o nickname                         // [ operator] make nickname as operator  
    MODE #channel_name +l number                           // [ operator]: set channel limit to < number>  
    MODE #channel_name +k newkey                           // [ operator]: set channel key  
    MODE #channel_name +t                                  // [ operator]: ghir operators li ghaychonjiw topic  
  
    MODE #channel_name -i                                  // [operator]  
    MODE #channel_name -o nickname                         // [operator] make nickname as normal user  
    MODE #channel_name -l                                  // [operator]: unset channel limit  
    MODE #channel_name -k                                  // [operator]: unset channel key  
    MODE #channel_name -t                                  // [operator]: anyone can set channel topic    
  
    MODE #channel_name +iolkt nickname number newkey       // [operator]  
    MODE #channel_name -iolkt nickname                     // [operator]  
    MODE #channel_name +io-lkt nickname                    // [operator]  
    MODE #channel_name +i+o+l+k+t -i nickname              // [operator]  
  
>PART:  
    PART #channel_name // [ anyone]  
  
>?PRIVMSG:  
    PRIVMSG #channel_name message              // [from channel users to hannel users only]  
    PRIVMSG nickname message                  // [from user to user even there is no channel between them]  
    PRIVMSG #channel_name :message with spaces // [from channel users to hannel users only]  
    PRIVMSG nickname message with spaces      // [from user to user even there is no channel between them]  
  
>QUIT:  
    QUIT // [ anyone] quit server and all channels  
  
>TOPIC:  
    ila kant MODE `+t`:  
        TOPIC #channel_name topic              // [ operator]  
        TOPIC #channel_name :topic with spaces // [ operator]  
    else:   
        TOPIC #channel_name topic              // [ anyone]  
        TOPIC #channel_name :topic with spaces // [ anyone]  
  
>PONG:  
    // ignored command  
    PONG  
    PONG ...  


**How tasks should be handled**

- main  
case PASS:  
PASS password  
PASS :password contains spaces  
case NICK:  
NICK nickname  
NICK :nickname  
case USER:  
//ps: realname makhasch ikon fih numberss  
USER username <(chi 7aja ignored)> <(chi 7aja ignored)> realname  
case JOIN:  
JOIN #name  
JOIN #name1,#name2  
JOIN #name1,#name2 key1  
JOIN #name1,#name2 key1,key2  
case PRIVMSG:  
PRIVMSG <channel or nickname> message  
PRIVMSG <channel or nickname> :message with spaces  
case KICK:  
// khas tkon operator  
KICK <channel name> <nickname> [raison]  
case INVITE:  
// khas tkon operator  
INVITE nickname <channel>  
case TOPIC:  
// khas tkon operator il kan l mode dyal channel +t  
TOPIC channel_name // show the channel topics  
TOPIC channel_name topic  
TOPIC channel_name :topic with spaces  
case MODE:  
// khas tkon operator  
MODE channel_name // affich activated mode in channel can do it by any member in channel  
MODE channel_name +i // set channel mode to invite only  
MODE channel_name +t // il akan channel fiha mode topic, ghir operator eli kaybadlo topic  
MODE channel_name +k password// set password to the channel  
MODE channel_name +l limit// set limit to the channel AKA max users  
MODE channel_name +o nickname// set nickname as operator  
  
MODE channel_name -i // anyone can join the channel (beware ila kant channel 3dha password)  
MODE channel_name -t // anyone can set topic  
MODE channel_name -k old_password// unset password, now the channel is accesseble withour paassword  
MODE channel_name -l // the channel has no limit  
MODE channel_name -o nickname// set nickname default users  
  
MODE channel_name +itklo password limit nickname  
MODE channel_name +itkol password nickname limit  
  
MODE channel_name +itklo -itklo password limit nickname old_password nickname  
MODE channel_name +itkol -itkol password nickname old_password nickname  
  
MODE channel_name +k password// set password to the channel  
MODE channel_name +k another_password// alredy set to channel, khask tdir `MODE channel_name -k old_password` 3ad y t setih  
  
  
case QUIT:  
QUIT // quit mn server  
QUIT reason // quit mn server with a reason  


**Problem 3end Mohammed**  
>mli katbghi t authentificati mli katkteb "nick" GHALAT KAYTCRASHA registration kamla  
>w t handli signal dyal sigpipe  
>./ircserv 8080 " "
