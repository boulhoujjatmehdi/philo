/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:00:40 by eboulhou          #+#    #+#             */
/*   Updated: 2023/06/07 13:45:16 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_phil *philo)
{
	int		philo_id;
	t_gen	*gen;

	philo_id = philo->id;
	gen = philo->gen;
	if (philo_id == philo->gen->philo_nb)
		philo_id = 0;
	pthread_mutex_lock(&philo->gen->frk[philo->id - 1]);
	lock_print(1, philo);
	pthread_mutex_lock(&philo->gen->frk[philo_id]);
	lock_print(1, philo);
	lock_print(2, philo);
	pthread_mutex_lock(&gen->_last[philo->id - 1]);
	philo->last_eat = get_time(gen->mill_time);
	pthread_mutex_unlock(&gen->_last[philo->id - 1]);
	usleep_inou(gen->time_eat, philo);
	pthread_mutex_lock(&gen->c);
	philo->nb_eat++;
	if (philo->nb_eat == philo->gen->cycle_eat)
		philo->gen->cycle_count++;
	pthread_mutex_unlock(&gen->c);
	pthread_mutex_unlock(&philo->gen->frk[philo_id]);
	pthread_mutex_unlock(&philo->gen->frk[philo->id - 1]);
}

void	*philo_thread(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	pthread_mutex_lock(&philo->gen->_last[philo->id - 1]);
	philo->last_eat = get_time(philo->gen->mill_time);
	pthread_mutex_unlock(&philo->gen->_last[philo->id - 1]);
	while (1)
	{
		pthread_mutex_lock(&philo->gen->s);
		if (*philo->stop)
		{
			pthread_mutex_unlock(&philo->gen->s);
			break ;
		}
		pthread_mutex_unlock(&philo->gen->s);
		lock_print(4, philo);
		eating(philo);
		lock_print(3, philo);
		usleep_inou(philo->gen->time_sleep, philo);
	}
	return (NULL);
}

t_phil	*create_philos(t_gen *gen, int *stop)
{
	int		i;
	t_phil	*philo;

	i = 0;
	philo = ft_calloc(sizeof(t_phil), gen->philo_nb + 1);
	gen->frk = ft_calloc(sizeof(pthread_mutex_t), gen->philo_nb);
	gen->_last = ft_calloc(sizeof(pthread_mutex_t), gen->philo_nb);
	i = pthread_mutex_init(&gen->s, NULL) + pthread_mutex_init(&gen->c, NULL)
		+ pthread_mutex_init(&gen->print, NULL);
	if (i || !gen->frk || !philo || !gen->_last)
		return (NULL);
	i = 0;
	while (i < gen->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].gen = gen;
		philo[i].stop = stop;
		pthread_mutex_init(&philo[i].gen->frk[i], NULL);
		pthread_mutex_init(&philo[i].gen->_last[i], NULL);
		i++;
	}
	gen->mill_time = get_time(0);
	return (philo);
}

int	start_philoes(t_gen *gen, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < gen->philo_nb)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			return (1);
		i += 2;
		usleep(10);
	}
	i = 1;
	while (i < gen->philo_nb)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			return (1);
		i += 2;
		usleep(2);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_gen	gen;
	t_phil	*philo;
	int		stop;

	stop = 0;
	if (!initialize_data(&gen, ac, av))
		return (1);
	philo = create_philos(&gen, &stop);
	if (!philo)
		return (1);
	if (start_philoes(&gen, philo))
		return (1);
	monitoring(&gen, philo);
	destroy_all(&gen, philo);
}
