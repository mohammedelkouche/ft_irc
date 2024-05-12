NAME = ircserv

SRC = ./mandatory/main.cpp ./mandatory/client.cpp ./mandatory/server.cpp

OBJ = $(SRC:.cpp=.o)

HEADER =  ./include/server.hpp ./include/client.hpp

CFLAGS = -Wall -Wextra -Werror -std=c++98

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