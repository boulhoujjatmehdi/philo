NAME=philo

CC= cc -Wall -Wextra -Werror \
	# -g -fsanitize=thread


SRC= philo.c utils.c utils1.c utils2.c

all:$(NAME)

clean :
	rm -rf *.o
fclean: clean
	rm -rf $(NAME)
re:	fclean all

$(NAME): $(SRC) philo.h Makefile
	$(CC) $(SRC) -o $@

