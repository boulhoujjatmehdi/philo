/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:00:40 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/27 20:26:14 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void eating(t_phil *philo)
{
	int philo_id;
	philo_id = philo->id;
	t_gen *gen = philo->gen;
	if (philo_id == philo->gen->philo_nb)
		philo_id = 0;
	pthread_mutex_lock(&philo->gen->frk[philo->id - 1]);
	pthread_mutex_lock(&gen->print);
	printf("%ld %d has taken a fork\n", get_time(philo->gen, 1), philo->id);
	pthread_mutex_unlock(&gen->print);
	pthread_mutex_lock(&philo->gen->frk[philo_id]);
	pthread_mutex_lock(&gen->print);
	printf("%ld %d has taken a fork\n", get_time(philo->gen, 1), philo->id);
	pthread_mutex_unlock(&gen->print);
	pthread_mutex_lock(&gen->print);
	printf("%ld %d is eating\n", get_time(philo->gen, 1), philo->id);
	pthread_mutex_unlock(&gen->print);
	pthread_mutex_lock(&gen->_last[philo->id - 1]);
	philo->last_eat = get_time(gen, 1);
	pthread_mutex_unlock(&gen->_last[philo->id - 1]);
	usleep_inou(gen->time_eat, gen);
	pthread_mutex_lock(&gen->count);
	philo->nb_eat++;
	if(philo->nb_eat == philo->gen->cycle_eat)
		philo->gen->cycle_count ++;
	pthread_mutex_unlock(&gen->count);
	pthread_mutex_unlock(&philo->gen->frk[philo_id]);
	pthread_mutex_unlock(&philo->gen->frk[philo->id - 1]);
}

void sleeping(t_phil *philo)
{
	pthread_mutex_lock(&philo->gen->print);
	printf("%ld %d is sleeping\n", get_time(philo->gen, 1), philo->id);
	pthread_mutex_unlock(&philo->gen->print);
	usleep_inou(philo->gen->time_sleep, philo->gen);
}

void thinking(t_phil *philo)
{
	pthread_mutex_lock(&philo->gen->print);
	printf("%ld %d is thinking\n", get_time(philo->gen, 1), philo->id);
	pthread_mutex_unlock(&philo->gen->print);
}

void *philo_thread(void *arg)
{
	t_phil *philo;

	philo = (t_phil *)arg;
	pthread_mutex_lock(&philo->gen->_last[philo->id - 1]);
	philo->last_eat = get_time(philo->gen, 1);
	pthread_mutex_unlock(&philo->gen->_last[philo->id - 1]);
	while (1)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return NULL;
}

t_phil *create_philos(t_gen *gen)
{
	int i;
	t_phil *philo;
	philo = calloc(sizeof(t_phil), gen->philo_nb + 1);
	gen->frk = calloc(sizeof(pthread_mutex_t), gen->philo_nb);
	gen->_last = calloc(sizeof(pthread_mutex_t), gen->philo_nb);
	pthread_mutex_init(&gen->last, NULL);
	pthread_mutex_init(&gen->count, NULL);
	pthread_mutex_init(&gen->print, NULL);
	i = 0;
	while (i < gen->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].gen = gen;
		pthread_mutex_init(&philo[i].gen->frk[i], NULL);
		pthread_mutex_init(&philo[i].gen->_last[i], NULL);
		i++;
	}
	return philo;
}

#include <string.h>
int main(int ac, char **av)
{
	int i;
	t_gen *gen;

	gen = calloc(sizeof(t_gen), 1);
	if(!initialize_data(gen, ac, av))
		return 1;
	t_phil *philo = create_philos(gen);
	gen->mill_time = get_time(gen, 0);
	i = 0;
	while (i < gen->philo_nb)
	{
		pthread_create(&philo[i].phil_thread, NULL, philo_thread, &philo[i]);
		i += 2;
		usleep(10);
	}
	i = 1;
	while (i < gen->philo_nb)
	{
		pthread_create(&philo[i].phil_thread, NULL, philo_thread, &philo[i]);
		i += 2;
		usleep(10);
	}
	i = 0;
		i = 0;
		long tmp;
		long time;
		int count;

		pthread_mutex_lock(&gen->_last[i]);
		tmp = philo[i].last_eat;
		pthread_mutex_unlock(&gen->_last[i]);
		pthread_mutex_lock(&gen->count);
		count = gen->cycle_count;
		pthread_mutex_unlock(&gen->count);
		time = get_time(gen, 1);
		while (count < gen->philo_nb && i < gen->philo_nb && get_time(gen, 1) - tmp < gen->time_die)
		{
			i++;
			if (i == gen->philo_nb)
				i = 0;
			pthread_mutex_lock(&gen->_last[i]);
			tmp = philo[i].last_eat;
			pthread_mutex_unlock(&gen->_last[i]);
			pthread_mutex_lock(&gen->count);
			count = gen->cycle_count;
			pthread_mutex_unlock(&gen->count);
		}
		pthread_mutex_lock(&gen->print);
		printf("%ld %d died\n", get_time(gen, 1), philo[i].id);
}
