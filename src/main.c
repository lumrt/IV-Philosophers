/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:43:02 by lucas             #+#    #+#             */
/*   Updated: 2024/11/26 15:08:21 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	data = (t_data) {0};
	if (ac < 5 || ac > 6)
		error_exit("Wrong Input\n ./philo nb ttdie tteat ttsleep [max]");
	parsing(&data, av);
	init_all(&data);		
	starting_simulation(&data);
	while(1)
	{
		if(!monitor_dinner(&data))
			break;
	}
	int i = -1;
	while (++i < data.nb_philo)
		safe_thread_handler(&data.philos[i].thread_index, NULL, NULL, JOIN);
	free_all(&data);
}