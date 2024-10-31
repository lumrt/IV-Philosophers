/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:43:32 by lucas             #+#    #+#             */
/*   Updated: 2024/10/29 17:54:13 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool is_dead(t_philo *philo)
{
    long    elps;
    long    t2die;

    if (get_b(&philo->philo_mtx, &philo->isfull))
        return (false);
    elps = gettime(MILLISECOND) - get_l(&philo->philo_mtx, philo->last_meal);
    t2die = philo->data->ttdie / 1e3;
    
    if (elps > t2die)
        return (true);
    return (false);
}

void    *monitor_dinner(void *data2)
{
    int i;
    t_data  *data;
    
    data = (t_data *)data2;
    while (!all_running(&data->variable_mtx, &data->nb_thread_run,
            data->nb_philo))
    ;
    while (!sim_finish(data))
    {
         i = -1;
         while(++i < data->nb_philo && !sim_finish(data))
         {
            if (is_dead(data->philos + i))
            {
                set_b(&data->variable_mtx, &data->is_end, true);
                write_status(DIED, data->philos + i, DEBUG_MODE);
            }
         }
    }
    return (NULL); 
}