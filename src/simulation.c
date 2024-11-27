/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:28:49 by lucas             #+#    #+#             */
/*   Updated: 2024/11/27 17:23:50 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sync_threads(philo->data);
	set_l(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	increase_l(&philo->data->variable_mtx, &philo->data->nb_thread_run);
	write_status(TAKING_FIRST_FORK, philo);
	while (!sim_finish(philo->data))
		usleep(300);
	return (NULL);
}

static void	think(t_philo *philo)
{
	write_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(TAKING_FIRST_FORK, philo);
	safe_mutex_handler(&philo->left_fork->fork, LOCK);
	write_status(TAKING_SECOND_FORK, philo);
	philo->meal_counter++;
	write_status(EATING, philo);
	set_l(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	sharper_usleep(philo->data->tteat * 1000, philo->data);
	if (philo->data->max_meal > 0
		&& philo->meal_counter == philo->data->max_meal)
		set_b(&philo->philo_mtx, &philo->isfull, true);
	safe_mutex_handler(&philo->right_fork->fork, UNLOCK);
	safe_mutex_handler(&philo->left_fork->fork, UNLOCK);
}

void	*starting_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	safe_mutex_handler(philo->start_mtx, LOCK);
	safe_mutex_handler(philo->start_mtx, UNLOCK);
	set_l(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	while (!sim_finish(philo->data))
	{
		if (philo->isfull)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		sharper_usleep(philo->data->ttsleep * 1000, philo->data);
		think(philo);
		if ((philo->data->nb_philo % 2)
			&& philo->data->tteat >= philo->data->ttsleep)
			sharper_usleep((philo->data->tteat
					- philo->data->ttsleep + 10) * 1000, philo->data);
	}
	return (NULL);
}
