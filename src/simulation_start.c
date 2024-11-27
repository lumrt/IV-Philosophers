/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:28:49 by lucas             #+#    #+#             */
/*   Updated: 2024/11/27 16:55:17 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	start_even_philosophers(t_data *data)
{
	int	i;

	safe_mutex_handler(&data->start_mtx, LOCK);
	i = 0;
	while (i < data->nb_philo)
	{
		safe_thread_handler(&data->philos[i].thread_index,
			starting_dinner, &data->philos[i], CREATE);
		i += 2;
	}
	safe_mutex_handler(&data->start_mtx, UNLOCK);
}

static void	start_odd_philosophers(t_data *data)
{
	int	i;

	sharper_usleep(150, data);
	safe_mutex_handler(&data->start_mtx, LOCK);
	i = 1;
	while (i < data->nb_philo)
	{
		safe_thread_handler(&data->philos[i].thread_index,
			starting_dinner, &data->philos[i], CREATE);
		i += 2;
	}
	safe_mutex_handler(&data->start_mtx, UNLOCK);
}

void	starting_simulation(t_data *data)
{
	if (data->max_meal == 0)
		return ;
	else if (data->nb_philo == 1)
	{	
		data->simulation_date = gettime(MILLISECOND);
		safe_thread_handler(&data->philos[0].thread_index,
			ft_alone, &data->philos[0], CREATE);
	}
	else
	{
		data->simulation_date = gettime(MILLISECOND);
		start_even_philosophers(data);
		start_odd_philosophers(data);
	}
	set_b(&data->variable_mtx, &data->trheads_sync, true);
}
