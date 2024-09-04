/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:54:41 by lucas             #+#    #+#             */
/*   Updated: 2024/09/04 17:30:18 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_init(t_data *data)
{
	//
}
void    data_init(t_data *data)
{
	int	i;

	i = 0;
	data->is_end = false;
	data->philos = safe_malloc_handle(sizeof(t_philo) * data->nb_philo); // TOFIX
	data->forks = safe_malloc_handle(sizeof(t_fork) * data->nb_philo);
	while (i <= data->nb_philo)
	{
		safe_mutex_handler(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data); // TODO
}