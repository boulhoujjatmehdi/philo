/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:00:40 by eboulhou          #+#    #+#             */
/*   Updated: 2023/06/03 20:03:20 by eboulhou         ###   ########.fr       */
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
	sem_wait(gen->frk);
	// sem_wait(gen->frk);
	
	lock_print(1, philo);
	lock_print(1, philo);
	lock_print(2, philo);
	philo->last_eat = get_time(gen->mill_time);
	usleep_inou(gen->time_eat);

	philo->nb_eat++;
	if (philo->nb_eat == philo->gen->cycle_eat)
		philo->gen->cycle_count++;

	sem_post(gen->frk);
	// sem_post(gen->frk);
}


void	*philo_thread(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	philo->last_eat = get_time(philo->gen->mill_time);
	while (philo->last_eat + philo->gen->time_die > get_time(philo->gen->mill_time))
	{
		if (*philo->stop)
		{
			break ;
		}
		lock_print(4, philo);
		eating(philo);
		lock_print(3, philo);
		usleep_inou(philo->gen->time_sleep);
	}
	// printf("%ld %d died\n(%ld) (%ld)\n", get_time(philo->gen->mill_time), philo->id, philo->last_eat + philo->gen->time_die ,  get_time(philo->gen->mill_time)+100);
	return (NULL);
}

// int child_monitor(t_phil *philo)
// {

// }

void philo_child(t_phil *philo)
{
	pthread_create(&philo->thread, NULL, philo_thread, philo);
	// child_monitor(philo);
	pthread_join(philo->thread, NULL);
	// printf("hello from child nb = %d\n", philo->id);
	exit(44);
	
}

t_phil	*create_philos(t_gen *gen, int *stop)
{
	int		i;
	t_phil	*philo;

	i = 0;
	philo = ft_calloc(sizeof(t_phil), gen->philo_nb + 1);
	gen->pid = ft_calloc(sizeof(int), gen->philo_nb);
	gen->_last = ft_calloc(sizeof(sem_t), gen->philo_nb);
	i = 0;
	char str[] = "mehdi1";
	sem_unlink(str);
	gen->frk = sem_open(str, O_CREAT | O_EXCL, 0666, gen->philo_nb / 2);
	str[0] = '0';
	gen->print = sem_open(str, O_CREAT | O_EXCL, 0666, 1);
	if(gen->frk == SEM_FAILED)
		exit(10);
	while (i < gen->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].gen = gen;
		philo[i].stop = stop;
		i++;
	}
	gen->mill_time = get_time(0);
	return (philo);
}

int	start_philoes(t_gen *gen, t_phil *philo)
{
	int	i;

	i = 0;

	while(i < gen->philo_nb)
	{
		gen->pid[i] = fork();
		if(gen->pid[i] == 0)
		{
			philo_child(&philo[i]);
		}
		i++;
	}
	return (0);
}

#include <signal.h>

int	main(int ac, char **av)
{
	t_gen	gen;
	t_phil	*philo;
	int		stop;
	int		i;
	stop = 0;
	if (!initialize_data(&gen, ac, av))
		return (1);
	philo = create_philos(&gen, &stop);
	if (!philo)
		return (1);
	if (start_philoes(&gen, philo))
		return (1);
	wait(NULL);
	sem_wait(gen.print);
	i = 0;
	printf("died\n");
	while(i < gen.philo_nb)
	{
		kill(gen.pid[i], SIGINT);
		i++;
	}
	// pause();
	sem_post(gen.print);
}
