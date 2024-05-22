# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 16:54:34 by mel-kouc          #+#    #+#              #
#    Updated: 2024/05/22 18:50:29 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC = ./mandatory/main.cpp ./mandatory/client.cpp ./mandatory/server.cpp \
		./mandatory/authentication.cpp ./mandatory/utils_authn.cpp \
			./mandatory/topic.cpp ./mandatory/InviteCommand.cpp \
			./mandatory/JoinCommand.cpp ./mandatory/channels.cpp 

OBJ = $(SRC:.cpp=.o)

HEADER =  ./include/server.hpp ./include/client.hpp ./include/topic.hpp \
            ./include/channels.hpp ./include/reply.hpp

CFLAGS = -Wall -Wextra -Werror  -std=c++98 -fsanitize=address -g

CC = c++

all :: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp $(HEADER)
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re:	fclean all