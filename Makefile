NAME=philo/philo
B_NAME=bonus/philo_bonus

CC= cc -Wall -Wextra -Werror \
	# -g -fsanitize=thread

OBJ= philo/philo.o philo/utils.o philo/utils1.o philo/utils2.o 
BNS_OBJ= bonus/philo.o bonus/utils.o bonus/utils1.o bonus/utils2.o 


all:$(NAME)
 
bonus:$(B_NAME)

$(B_NAME): $(BNS_OBJ) bonus/philo.h Makefile
	$(CC) $(BNS_OBJ) -o $@

clean :
	rm -rf $(OBJ) $(BNS_OBJ)
fclean: clean
	rm -rf $(NAME) $(B_NAME)
re:	fclean all


$(NAME): $(OBJ) philo/philo.h Makefile
	$(CC) $(OBJ) -o $@
	
%.o:%.c
	$(CC) -c $< -o $@ 
