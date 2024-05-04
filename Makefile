# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 16:54:34 by mel-kouc          #+#    #+#              #
#    Updated: 2024/05/04 15:40:30 by mel-kouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC = ./mandatory/main.cpp ./mandatory/client.cpp ./mandatory/server.cpp

HEADER = ./include/client.hpp ./include/server.hpp

CFLAGS = -Wall -Wextra -Werror -std=c++98

CC = c++

OBJ = $(SRC:.c=.o)


all :: $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER) $(Bonus_HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
		rm -rf $(OBJ) $(BOBJ)

fclean: clean
		rm -rf $(NAME) $(BNAME)

re:	fclean all