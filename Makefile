NAME=philo/philo
B_NAME=bonus/philo_bonus

CC= cc -Wall -Wextra -Werror

OBJ= philo/philo.o philo/utils.o philo/utils1.o philo/utils2.o 


all:$(NAME)

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

$(NAME): $(OBJ) philo/philo.h Makefile
	$(CC) $(OBJ) -o $@
	
%.o:%.c
	$(CC) -c $< -o $@ 
