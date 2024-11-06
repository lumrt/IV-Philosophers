/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:09:30 by lucas             #+#    #+#             */
/*   Updated: 2024/11/06 20:15:31 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (status == TAKING_FIRST_FORK && !sim_finish(philo->data))
        printf("%-6ld %d has taken first fork 🍴\n", elapsed ,philo->index);
    else if (status == TAKING_SECOND_FORK && !sim_finish(philo->data))
        printf("%-6ld %d has taken second fork 🍴\n", elapsed ,philo->index);
    else if (status == EATING && !sim_finish(philo->data))
        printf("%-6ld %d is eating 🍜\n", elapsed, philo->index);
    else if (status == SLEEPING && !sim_finish(philo->data))
        printf("%-6ld %d is sleeping 😴\n", elapsed, philo->index);
    else if (status == THINKING && !sim_finish(philo->data))
        printf("%-6ld %d is thinking 🤔\n", elapsed, philo->index);
    else if (status == DIED)
        printf("%-6ld %d just died 💀\n", elapsed, philo->index);
}

void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND) - philo->data->simulation_date;

    if (philo->isfull)
        return ;

    safe_mutex_handler(&philo->data->write_mtx, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed); // TODO  
    else 
    {
        if ((status == TAKING_FIRST_FORK || status == TAKING_FIRST_FORK) 
            && !sim_finish(philo->data))
            printf("%-6ld %d has taken a fork\n", elapsed ,philo->index);
        else if (status == EATING && !sim_finish(philo->data))
            printf("%-6ld %d is eating\n", elapsed, philo->index);
        else if (status == SLEEPING && !sim_finish(philo->data))
            printf("%-6ld %d is sleeping\n", elapsed, philo->index);
        else if (status == THINKING && !sim_finish(philo->data))
            printf("%-6ld %d is thinking\n", elapsed, philo->index);
        else if (status == DIED)
            printf("%-6ld %d died\n", elapsed, philo->index);
    }
    safe_mutex_handler(&philo->data->write_mtx, UNLOCK);
}