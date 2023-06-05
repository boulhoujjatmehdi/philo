/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:23:07 by eboulhou          #+#    #+#             */
/*   Updated: 2023/06/05 18:21:08 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long diff)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (((timev.tv_sec * 1000) + (timev.tv_usec / 1000)) - diff);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	ret;
	int		neg;

	i = 0;
	ret = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if ((str[i] == '-' || str[i] == '+') && ++i)
		if (str[i - 1] == '-')
			neg = -1;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + str[i] - 48;
		if ((ret > 2147483647 && neg == 1) || (ret > 2147483648 && neg == -1))
			return (-1);
		i++;
	}
	if (str[i])
		return (-1);
	return (ret * neg);
}

void	usleep_inou(int tm)
{
	long	time;

	time = get_time(0) + tm;
	while (time > get_time(0))
		usleep(250);
}

int	initialize_data(t_gen *gen, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	gen->philo_nb = ft_atoi(av[1]);
	if (gen->philo_nb <= 0 || gen->philo_nb > 200)
		return (0);
	gen->time_die = ft_atoi(av[2]);
	if (gen->time_die < 0)
		return (0);
	gen->time_eat = ft_atoi(av[3]);
	if (gen->time_eat < 60)
		return (0);
	gen->time_sleep = ft_atoi(av[4]);
	if (gen->time_sleep < 60)
		return (0);
	if (av[5])
	{
		gen->cycle_eat = ft_atoi(av[5]);
		if (gen->cycle_eat <= 0)
			return (0);
	}
	else
		gen->cycle_eat = -1;
	return (1);
}
