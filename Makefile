# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 16:54:34 by mel-kouc          #+#    #+#              #
#    Updated: 2024/05/17 18:54:44 by mel-kouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC = ./mandatory/main.cpp ./mandatory/client.cpp ./mandatory/server.cpp ./mandatory/authentication.cpp ./mandatory/utils_authn.cpp
OBJ = $(SRC:.cpp=.o)

HEADER =  ./include/server.hpp ./include/client.hpp

CFLAGS = -Wall -Wextra -Werror  -std=c++98 -fsanitize=address

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