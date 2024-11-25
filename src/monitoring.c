/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:43:32 by lucas             #+#    #+#             */
/*   Updated: 2024/11/07 21:24:44 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_dead(t_philo *philo)
{
	if ((gettime(MILLISECOND) - get_l(&philo->philo_mtx, &philo->last_meal)) >= philo->data->ttdie)
	{
		return 1;
	}
	return (0);
}

int	monitor_dinner(t_data *data)
{
	int i;
	bool	all_full;

	i = -1;
	all_full = true;
	while (++i < data->nb_philo && !sim_finish(data))
	{
		all_full = all_full && get_b(&data->philos[i].philo_mtx, &data->philos[i].isfull);
		if (is_dead(data->philos + i))
		{
			set_b(&data->variable_mtx, &data->is_end, true);
			write_status(DIED, data->philos + i, DEBUG_MODE);
			return (0);
		}
	}
	return (!all_full);
}