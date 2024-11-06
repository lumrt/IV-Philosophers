/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:43:02 by lucas             #+#    #+#             */
/*   Updated: 2024/11/06 18:21:38 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	data = (t_data) {0};
	data.debug_mode = (ac == 7);
	if (ac == 5 || ac == 6 || ac == 7)
	{
		parsing(&data, av);
		init_all(&data);		
		starting_simulation(&data);

		while(1)
		{
			if(!monitor_dinner(&data))
				break;
		}
		
		// 4) when philo is full | 1 philo died 
	}
	int i = -1;
	while (++i < data.nb_philo)
		safe_thread_handler(&data.philos[i].thread_index, NULL, NULL, JOIN);
	// else
	// 	error_exit("Wrong Input\n ./philo nb ttdie tteat ttsleep [max]");
}