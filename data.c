/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:54:41 by lucas             #+#    #+#             */
/*   Updated: 2024/10/15 15:46:22 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->nb_philo;
	philo->right_fork = &forks[(position + 1) % philo_nbr];
	philo->left_fork = &forks[position];
	if (philo->index % 2 == 0)
	{
		philo->right_fork = &forks[position];
		philo->left_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philos + i;
		philo->index = i + 1;
		philo->isfull = false;
		philo->meal_counter = 0;
		philo->data = data;
		safe_mutex_handler(&philo->philo_mtx, INIT);
		if (data->debug_mode)
			printf("le philo %d a bien ete initialisé\n", philo->index);
		assign_forks(philo, data->forks, i);
		if (data->debug_mode)
			printf("ses fourchettes egalements\n\n");
		i++;
	}
}
void    init_all(t_data *data)
{
	int	i;

	i = 0;
	data->is_end = false;
	data->trheads_sync = false;
	data->nb_thread_run = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		error_exit("malloc failed");
	safe_mutex_handler(&data->variable_mtx, INIT);
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		error_exit("malloc failed");
	while (i < data->nb_philo)
	{
		safe_mutex_handler(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
		i++;
	}
	philo_init(data);
}
