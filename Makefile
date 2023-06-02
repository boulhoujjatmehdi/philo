NAME=philo

CC= cc -Wall -Wextra -Werror \
	# -g -fsanitize=thread

OBJ= mandatory/philo.o mandatory/utils.o mandatory/utils1.o mandatory/utils2.o 
BNS_OBJ= bonus/philo.o bonus/utils.o bonus/utils1.o bonus/utils2.o 

all:$(NAME)
 
bonus:

clean :
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re:	fclean all

$(NAME): $(OBJ) mandatory/philo.h Makefile
	$(CC) $(OBJ) -o $@
	

