/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:43:32 by lucas             #+#    #+#             */
/*   Updated: 2024/11/06 18:50:46 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_dead(t_philo *philo)
{
	if (get_b(&philo->philo_mtx, &philo->isfull))
		return (false);
	// printf("%ld last meal\n", gettime(MILLISECOND) - philo->last_meal );
	if ((gettime(MILLISECOND) - get_l(&philo->philo_mtx, &philo->last_meal)) >= philo->data->ttdie)
	{
		return 1;
	}
	return (0);
}

int	monitor_dinner(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_philo && !sim_finish(data))
	{
		// printf("asddsa\n");
		if (is_dead(data->philos))
		{
			printf("philo nb %d died\n", data->philos->index);
			set_b(&data->variable_mtx, &data->is_end, true);
			write_status(DIED, data->philos + i, DEBUG_MODE);
			return (0);
		}
	}
	return (1);
}