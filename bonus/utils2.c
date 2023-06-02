/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:14:27 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/31 19:26:48 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_val(void *val, pthread_mutex_t *mtx)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *(long *)val;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	monitoring(t_gen *gen, t_phil *philo)
{
	int	i;

	i = 0;
	gen->t_tmp = get_val(&philo[i].last_eat, &gen->_last[i]);
	gen->t_count = get_val(&gen->cycle_count, &gen->c);
	while (gen->t_count < gen->philo_nb && i < gen->philo_nb
		&& get_time(gen->mill_time) - gen->t_tmp < gen->time_die)
	{
		i++;
		if (i == gen->philo_nb)
			i = 0;
		gen->t_tmp = get_val(&philo[i].last_eat, &gen->_last[i]);
		gen->t_count = get_val(&gen->cycle_count, &gen->c);
	}
	pthread_mutex_lock(&gen->s);
	*philo->stop = 1;
	pthread_mutex_unlock(&gen->s);
	pthread_mutex_lock(&gen->print);
	if (gen->t_count != gen->philo_nb)
		printf("%ld %d died\n", get_time(gen->mill_time), philo[i].id);
	pthread_mutex_unlock(&gen->print);
}

int	destroy_all(t_gen *gen, t_phil *philo)
{
	int	i;

	i = -1;
	while (++i < gen->philo_nb)
		pthread_join(philo[i].thread, NULL);
	pthread_mutex_destroy(&gen->s);
	pthread_mutex_destroy(&gen->c);
	pthread_mutex_destroy(&gen->print);
	i = 0;
	while (i < gen->philo_nb)
	{
		pthread_mutex_destroy(&gen->_last[i]);
		pthread_mutex_destroy(&gen->frk[i]);
		i++;
	}
	free(philo);
	free(gen->frk);
	free(gen->_last);
	return (0);
}
