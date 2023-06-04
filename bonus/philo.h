/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:00 by eboulhou          #+#    #+#             */
/*   Updated: 2023/06/03 19:27:24 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
// #include <dispatch/dispatch.h>
# include <semaphore.h>
//--- TO DELETE ----
//--- TO DELETE ----

typedef struct s_gen
{
	int				philo_nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				cycle_eat;
	int				cycle_count;
	long			mill_time;
	struct timeval	time;
	sem_t			*frk;
	pthread_mutex_t	s;
	pthread_mutex_t	c;
	sem_t			*_last;
	sem_t			*print;
	long			t_tmp;
	long			t_time;
	int				t_count;
	// bonus
	int				*pid;
}t_gen;

typedef struct s_phil
{
	int			id;
	t_gen		*gen;
	int			*stop;
	pthread_t	thread;
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

//utils 2
long	get_val(void *val, pthread_mutex_t *mtx);
void	monitoring(t_gen *gen, t_phil *philo);
int		destroy_all(t_gen *gen, t_phil *philo);

#endif