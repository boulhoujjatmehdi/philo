/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:00:40 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/29 20:37:44 by eboulhou         ###   ########.fr       */
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
	usleep_inou(gen->time_eat);
	pthread_mutex_lock(&gen->count);
	philo->nb_eat++;
	if (philo->nb_eat == philo->gen->cycle_eat)
		philo->gen->cycle_count++;
	pthread_mutex_unlock(&gen->count);
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
		lock_print(4, philo);
		eating(philo);
		lock_print(3, philo);
		usleep_inou(philo->gen->time_sleep);
	}
	return (NULL);
}

t_phil	*create_philos(t_gen *gen)
{
	int		i;
	t_phil	*philo;

	philo = ft_calloc(sizeof(t_phil), gen->philo_nb + 1);
	gen->frk = ft_calloc(sizeof(pthread_mutex_t), gen->philo_nb);
	gen->_last = ft_calloc(sizeof(pthread_mutex_t), gen->philo_nb);
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
	return (philo);
}

void	monitoring(t_gen *gen, t_phil *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&gen->_last[i]);
	gen->t_tmp = philo[i].last_eat;
	pthread_mutex_unlock(&gen->_last[i]);
	pthread_mutex_lock(&gen->count);
	gen->t_count = gen->cycle_count;
	pthread_mutex_unlock(&gen->count);
	while (gen->t_count < gen->philo_nb && i < gen->philo_nb
		&& get_time(gen->mill_time) - gen->t_tmp < gen->time_die)
	{
		i++;
		if (i == gen->philo_nb)
			i = 0;
		pthread_mutex_lock(&gen->_last[i]);
		gen->t_tmp = philo[i].last_eat;
		pthread_mutex_unlock(&gen->_last[i]);
		pthread_mutex_lock(&gen->count);
		gen->t_count = gen->cycle_count;
		pthread_mutex_unlock(&gen->count);
	}
	pthread_mutex_lock(&gen->print);
	if (gen->t_count != gen->philo_nb)
		printf("%ld %d died\n", get_time(gen->mill_time), philo[i].id);
}

int	main(int ac, char **av)
{
	int		i;
	t_gen	*gen;
	t_phil	*philo;

	gen = ft_calloc(sizeof(t_gen), 1);
	if (!initialize_data(gen, ac, av))
		return (1);
	philo = create_philos(gen);
	gen->mill_time = get_time(0);
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
	monitoring(gen, philo);
}
