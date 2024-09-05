GREEN = \033[32m
BLUE = \033[34m
PURPLE = \033[35m
RED = \033[0;31m
ORANGE = \033[38;5;208m
COLOR_OFF = \033[0m
NAME = ircserv
BNAME = ircserv_bonus

SRC = ./mandatory/main.cpp ./mandatory/client.cpp \
	./mandatory/server.cpp ./mandatory/JoinCommand.cpp ./mandatory/channels.cpp \
	./mandatory/InviteCommand.cpp ./mandatory/KickCommand.cpp ./mandatory/PartCommand.cpp ./mandatory/authentication.cpp \
	./mandatory/utils_authn.cpp ./mandatory/topic.cpp ./mandatory/PrivateMessage.cpp ./mandatory/ModeCommande.cpp

BONUS = ./bonus/bonus_main.cpp ./bonus/bot_bonus.cpp

OBJ = $(SRC:.cpp=.o)
 
HEADER =  ./include/server.hpp ./include/client.hpp  ./include/channels.hpp ./include/reply.hpp ./include/global.hpp

BOBJ = $(BONUS:.cpp=.o)

HEADER_bonus =  ./include/bot_bonus.hpp

CFLAGS = -Wall -Wextra -Werror  -std=c++98 -fsanitize=address -g

CC = c++

all :: $(NAME)
		@echo "${BLUE} ⭐ Mandatory Compiled successfully 🚀 ✅${COLOR_OFF}"

bonus : $(BNAME)
		@echo "${PURPLE} ⭐ Bonus Compiled successfully 🚀 ✅${COLOR_OFF}"

$(NAME) : $(OBJ) $(HEADER)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BNAME) : $(BOBJ) $(HEADER_bonus)
		@$(CC)  $(CFLAGS) $(BOBJ) -o $(BNAME)

%.o : %.cpp $(HEADER) $(HEADER_bonus)
	@printf "${GREEN}Compiling 💻 $<...  🚀  ${COLOR_OFF}\n\r"
	@$(CC) $(CFLAGS)  -c $< -o $@

clean:
		@rm -rf $(OBJ) $(BOBJ)

fclean: clean
		@rm -rf $(NAME) $(BNAME)
		@echo "${ORANGE}Cleaned successfully 🧹 🗑️ ${COLOR_OFF}"

re:	fclean all
