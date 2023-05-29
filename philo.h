/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:00 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/29 20:38:53 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
//--- TO DELETE ----
//--- TO DELETE ----

typedef struct s_gen
{
	int				philo_nb;
	int				forks_nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				cycle_eat;
	int				cycle_count;
	long			mill_time;
	struct timeval	time;
	pthread_mutex_t	*frk;
	pthread_mutex_t	last;
	pthread_mutex_t	count;
	pthread_mutex_t	*_last;
	pthread_mutex_t	print;
	long			t_tmp;
	long			t_time;
	int				t_count;
}t_gen;

typedef struct s_phil
{
	int			id;
	t_gen		*gen;
	pthread_t	phil_thread;
	long		last_eat;
	int			nb_eat;
}t_phil;

//utils

//if diff=0 returns the 
long	get_time(long diff);
int		ft_atoi(const char *str);
void	usleep_inou(int tm);
int		initialize_data(t_gen *gen, int ac, char **av);

//utils 1 
void	lock_print(int idx, t_phil *philo);
void	*ft_calloc(size_t count, size_t size);

#endif