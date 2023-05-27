/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:00 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/27 19:32:40 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_gen
{
	int philo_nb;
	int forks_nb;
	int time_die;
	int time_eat;
	int time_sleep;
	int cycle_eat;
	int cycle_count;
	long mill_time;
	struct timeval time;
	pthread_mutex_t *frk;
	pthread_mutex_t last;
	pthread_mutex_t count;
	pthread_mutex_t *_last;
	pthread_mutex_t print;
}t_gen;


typedef struct s_phil
{
	int id;
	t_gen *gen;
	pthread_t phil_thread;
	long last_eat;
	int nb_eat;
}t_phil;

//if bol=1 return the diff
//if bol=0 return the today to 1970 time
long get_time(t_gen *gen, int bol);
int	ft_atoi(const char *str);

#endif