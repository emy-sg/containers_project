NAME = ft_containers

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm $(NAME)

fclean: clean

re: fclean all