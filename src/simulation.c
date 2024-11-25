/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:28:49 by lucas             #+#    #+#             */
/*   Updated: 2024/11/25 18:20:35 by lumaret          ###   ########.fr       */
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
	write_status(TAKING_FIRST_FORK, philo, DEBUG_MODE);
	while(!sim_finish(philo->data))
		usleep(300);
	return (NULL);
	
}

static void think(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void eat(t_philo *philo)
{
	safe_mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(TAKING_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handler(&philo->left_fork->fork, LOCK);
	write_status(TAKING_SECOND_FORK, philo, DEBUG_MODE);
	philo->meal_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	set_l(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	sharper_usleep(philo->data->tteat * 1000, philo->data);
	if (philo->data->max_meal > 0 && philo->meal_counter == philo->data->max_meal)
		set_b(&philo->philo_mtx, &philo->isfull, true);
	safe_mutex_handler(&philo->right_fork->fork, UNLOCK);
	safe_mutex_handler(&philo->left_fork->fork, UNLOCK);
}

void    starting_simulation(t_data *data)
{
	int	i;

	if (data->max_meal == 0)
		return ;
	else if (data->nb_philo == 1)
	{	
		data->simulation_date = gettime(MILLISECOND);
		safe_thread_handler(&data->philos[0].thread_index, ft_alone, &data->philos[0], CREATE);
	}
	else 
	{
		safe_mutex_handler(&data->start_mtx, LOCK);
		data->simulation_date = gettime(MILLISECOND);
		i = 0;
		while(i < data->nb_philo)
		{
			safe_thread_handler(&data->philos[i].thread_index,
			starting_dinner, &data->philos[i], CREATE);
			i += 2;
		}
		safe_mutex_handler(&data->start_mtx, UNLOCK);
		sharper_usleep(150, data);
		safe_mutex_handler(&data->start_mtx, LOCK);
		i = 1;
		while(i < data->nb_philo)
		{
			safe_thread_handler(&data->philos[i].thread_index,
			starting_dinner, &data->philos[i], CREATE);
			i += 2;
		}
		safe_mutex_handler(&data->start_mtx, UNLOCK);
	}
	set_b(&data->variable_mtx, &data->trheads_sync, true);	
}

void    *starting_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	safe_mutex_handler(philo->start_mtx, LOCK);
	safe_mutex_handler(philo->start_mtx, UNLOCK);
	set_l(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	while (!sim_finish(philo->data))
	{
		if (philo->isfull)
			break;
		eat(philo);
		
		write_status(SLEEPING, philo, DEBUG_MODE);
		sharper_usleep(philo->data->ttsleep * 1000, philo->data);
		think(philo);
		if ((philo->data->nb_philo % 2) && philo->data->tteat >= philo->data->ttsleep)
			sharper_usleep((philo->data->tteat - philo->data->ttsleep + 10) * 1000, philo->data);
	}
	return (NULL);
}