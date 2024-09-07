/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:28:49 by lucas             #+#    #+#             */
/*   Updated: 2024/09/07 18:31:21 by lucas            ###   ########.fr       */
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

void    *starting_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	sync_threads(philo->data); // TODO


	return (NULL);
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

}