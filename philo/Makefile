NAME=philo

CC= cc -Wall -Wextra -Werror \
	# -g -fsanitize=thread


OBJ= philo.o utils.o utils1.o utils2.o

all:$(NAME)

%.o:%.c 
	$(CC) $< -c  -o $@
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all


$(NAME): $(OBJ) philo.h Makefile
	$(CC) $(OBJ) -o $@

