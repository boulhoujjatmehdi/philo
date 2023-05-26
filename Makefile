NAME=philo

CC= cc -Wall -Wextra -Werror 

SRC= philo.c utils.c
	# -g fsanitize=thread

all:$(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $@
