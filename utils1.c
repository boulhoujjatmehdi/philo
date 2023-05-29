/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:54:01 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/29 20:38:10 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_print(int idx, t_phil *philo)
{
	long	time;

	pthread_mutex_lock(&philo->gen->print);
	time = get_time(philo->gen->mill_time);
	if (idx == 1)
		printf("%ld %d has taken a fork\n", time, philo->id);
	if (idx == 2)
		printf("%ld %d is eating\n", time, philo->id);
	if (idx == 3)
		printf("%ld %d is sleeping\n", time, philo->id);
	if (idx == 4)
		printf("%ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->gen->print);
}

void	ft_bzero(void *s, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	count *= size;
	ret = malloc(count);
	if (!ret)
		return (0);
	ft_bzero (ret, count);
	return (ret);
}
