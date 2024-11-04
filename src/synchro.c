/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:09:20 by lucas             #+#    #+#             */
/*   Updated: 2024/11/04 12:32:16 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// SPINLOCK 

void   sync_threads(t_data *data)
{
    while (!get_b(&data->variable_mtx, &data->trheads_sync))
        ;
}

bool    all_running(t_mutex *mutex, long *threads, long nb_philo)
{
    bool    rest;

    rest = false;
    safe_mutex_handler(mutex, LOCK);
    if (*threads == nb_philo)
        rest = true;
    safe_mutex_handler(mutex, UNLOCK);
     
    return (rest);
}
// to sync with the mon

void    increase_l(t_mutex *mtx, long *value)
{
    safe_mutex_handler(mtx, LOCK);
    (* value)++;
    safe_mutex_handler(mtx, UNLOCK);
}