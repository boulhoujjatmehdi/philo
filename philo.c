/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:00:40 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/23 15:20:23 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void take_fork(t_phil *philo)
{
	int philo_id;
	philo_id = philo->id;
	if (philo_id == philo->gen->philo_nb)
		philo_id = 0;

	pthread_mutex_lock(&philo->gen->frk[philo->id - 1]);
	printf("philo %d has taken a fork %d\n", philo->id, 1);
	pthread_mutex_lock(&philo->gen->frk[philo_id]);
	printf("philo %d has taken a fork %d\n", philo->id , 2);
	printf("philo %d is eating\n", philo->id);
	usleep(500000);
	pthread_mutex_unlock(&philo->gen->frk[philo_id]);
	pthread_mutex_unlock(&philo->gen->frk[philo->id - 1]);
	printf("philo %d is sleeping\n", philo->id);
	usleep(200);
	
}

void *philo_thread(void *arg)
{
	t_phil *philo;

	philo = (t_phil *)arg;
	while(1)
		take_fork(philo);

	return NULL; 
}
t_phil *create_philos(t_gen *gen)
{
	int i;
	t_phil *philo;
	// philo = calloc(sizeof(t_phil *), (gen->philo_nb + 1));
	philo = calloc(sizeof(t_phil), gen->philo_nb + 1);
	gen->frk = calloc(sizeof(pthread_mutex_t), gen->philo_nb);
	i = 0;
	while(i < gen->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].gen = gen;
		pthread_mutex_init(&philo[i].gen->frk[i], NULL);
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
	gen->philo_nb = atoi(av[1]);
	t_phil *philo = create_philos(gen);
	i = 0;

	gettimeofday(&gen->time, NULL);
	while(i < gen->philo_nb)
	{
		pthread_create(&philo[i].phil_thread, NULL, philo_thread, &philo[i]);
		i+=2;
		usleep(50);
	}
	i = 1;
	while(i < gen->philo_nb)
	{
		pthread_create(&philo[i].phil_thread, NULL, philo_thread, &philo[i]);
		i+=2;
		usleep(50);
	}
	// while(i < gen->philo_nb)
	// {
	// 	pthread_create(philo[i]->phil_thread, NULL, philo_thread, philo[i]);
	// 	i+=2;
	// }
	i = 0;
	
	while(i < gen->philo_nb)
	{
		pthread_join(philo[i].phil_thread, NULL);
		i++;
	}
	
}