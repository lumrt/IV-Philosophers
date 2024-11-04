/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:43:02 by lucas             #+#    #+#             */
/*   Updated: 2024/11/04 12:29:57 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	data = (t_data) {0};
	data.debug_mode = 0;
	if (ac == 7)
		data.debug_mode = 1;
	if (ac == 5 || ac == 6 || ac == 7)
	{
		parsing(&data, av);
		if (data.debug_mode)
		{
			printf("debug : nb philo = %ld\n", data.nb_philo);
			printf("debug : ttdie = %ld\n", data.ttdie);
			printf("debug : tteat = %ld\n", data.tteat);
			printf("debug : ttsleep = %ld\n", data.ttsleep);
			printf("debug : max meal = %ld\n\n", data.max_meal);
		}
		init_all(&data);		
		starting_simulation(&data);

		// 4) when philo is full | 1 philo died 
	}
	else
		error_exit("Wrong Input\n ./philo nb ttdie tteat ttsleep [max]");
}