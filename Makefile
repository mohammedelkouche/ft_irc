NAME = ircserv
BNAME = ircserv_bonus

SRC = ./mandatory/main.cpp ./mandatory/client.cpp \
	./mandatory/server.cpp ./mandatory/JoinCommand.cpp ./mandatory/channels.cpp \
	./mandatory/InviteCommand.cpp ./mandatory/KickCommand.cpp ./mandatory/PartCommand.cpp ./mandatory/authentication.cpp \
	./mandatory/utils_authn.cpp ./mandatory/topic.cpp ./mandatory/PrivateMessage.cpp

BONUS = ./bonus/bonus_main.cpp ./bonus/bot_bonus.cpp

OBJ = $(SRC:.cpp=.o)
 
HEADER =  ./include/server.hpp ./include/client.hpp  ./include/channels.hpp ./include/reply.hpp ./include/global.hpp

BOBJ = $(BONUS:.cpp=.o)

HEADER_bonus =  ./include/bot_bonus.hpp

CFLAGS = -Wall -Wextra -Werror  -std=c++98 -fsanitize=address -g

CC = c++

all :: $(NAME)

bonus : $(BNAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BNAME) : $(BOBJ) $(HEADER_bonus)
		$(CC)  $(CFLAGS) $(BOBJ) -o $(BNAME)

%.o : %.cpp $(HEADER) $(HEADER_bonus)
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
		rm -rf $(OBJ) $(BOBJ)

fclean: clean
		rm -rf $(NAME) $(BNAME)

re:	fclean all
