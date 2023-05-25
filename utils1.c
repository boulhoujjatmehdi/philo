/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:23:07 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/25 13:13:02 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(t_gen *gen, int bol)
{
	struct timeval timev;
	gettimeofday(&timev, NULL);
	if (bol)
		return (((timev.tv_sec * 1000) + (timev.tv_usec / 1000)) - gen->mill_time);
	return ((timev.tv_sec * 1000) + (timev.tv_usec / 1000));
}
