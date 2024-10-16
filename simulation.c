/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:28:49 by lucas             #+#    #+#             */
/*   Updated: 2024/10/15 15:47:45 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/* This is the file where all the simualtion is handled */
/* ./philo 5 800 500 500 [2]
    if no meals -> return ([0])
    create all threads and philos
    death monitor
    synch + join every threads
*/
//TODO
static void think(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

/*eat routine 
/* LOCK and announce that philo is taking the both forks, last meal time become gettime
philo meal counter is incremented, check if mealcounter == max meal and UNLOCK forks for 
the next philo*/

static void eat(t_philo *philo)
{
	safe_mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(TAKING_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handler(&philo->right_fork->fork, UNLOCK);
	write_status(TAKING_SECOND_FORK, philo, DEBUG_MODE);

	set_l(&philo->philo_mtx, philo->last_meal, gettime(MILLISECOND));
	philo->meal_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	sharper_usleep(philo->data->tteat, philo->data);
	if (philo->data->max_meal > 0 && philo->meal_counter == philo->data->max_meal)
		set_b(&philo->philo_mtx, &philo->isfull, true);
	safe_mutex_handler(&philo->right_fork->fork, UNLOCK);
	safe_mutex_handler(&philo->left_fork->fork, UNLOCK);
}

void    starting_simulation(t_data *data)
{
	int	i;

	i = -1;
	if (data->max_meal == 0)
		return ;
	else if (data->nb_philo == 1)
		;// handle when only one philo
	else 
		while(i++ < data->nb_philo)
		{
			safe_thread_handler(&data->philos[i].thread_index,
				starting_dinner, &data->philos[i], CREATE);
			
		}
	// monitoring
	safe_thread_handler(&data->monitor, monitor_dinner, data, CREATE);
	data->simulation_date = gettime(MILLISECOND);
	// now all threads ready 
	set_b(&data->variable_mtx, &data->trheads_sync, true);
	
	// Wait for al
	i = -1;
	while (i++ < data->nb_philo)
		safe_thread_handler(&data->philos[i].thread_index, NULL, NULL, JOIN);
	

}

static void    *starting_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	sync_threads(philo->data);
	increase_l(&philo->data->variable_mtx, &philo->data->nb_thread_run);
	while (!sim_finish(philo->data))
	{
		if (philo->isfull)
			break;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		sharper_usleep(philo->data->ttsleep, philo->data);
		think(philo);
	}

	return (NULL);
}