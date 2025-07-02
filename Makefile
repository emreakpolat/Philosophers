NAME=philo

CC=  cc -Wall -Wextra -Werror

SRC= main.c \
	philo_loop.c \
	philo_utils.c \
	parser_utils.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

re: fclean all

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

.PHONY: all re clean fclean