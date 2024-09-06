/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:54:41 by lucas             #+#    #+#             */
/*   Updated: 2024/09/05 16:25:06 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	// TODO
}

static void	philo_init(t_data *data)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (i++ < philo->nb_philo)
	{
		philo = data->philos + i;
		philo->index = i + 1;
		philo->isfull = false;
		philo->meal_counter = 0;
		philo->data = data;

		assign_forks(philo, data->forks, i);// TODO
	}
}
void    data_init(t_data *data)
{
	int	i;

	i = 0;
	data->is_end = false;
	data->philos = (t_philo *)safe_malloc_handle(sizeof(t_philo) * data->nb_philo); // TOFIX
	data->forks = safe_malloc_handle(sizeof(t_fork) * data->nb_philo);
	while (i <= data->nb_philo)
	{
		safe_mutex_handler(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
}
