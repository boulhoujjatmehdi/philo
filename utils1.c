/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:23:07 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/22 12:54:01 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil * new_fill()
{
    t_phil *new = malloc(sizeof(t_phil));
    if (!new)
        return NULL;
    new->id = 0;
    new->phil_thread = malloc(sizeof(pthread_t));
    return new;
}