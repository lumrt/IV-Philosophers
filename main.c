/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:43:02 by lucas             #+#    #+#             */
/*   Updated: 2024/09/07 16:29:24 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	data.debug_mode = 0;
	if (ac == 7)
		data.debug_mode = 1;
	if (ac == 5 || ac == 6 || ac == 7)
	{
		// 1) correct input + lexer
		parsing(&data, av);
		if (data.debug_mode)
		{
			printf("debug : nb philo = %ld\n", data.nb_philo);
			printf("debug : ttdie = %ld\n", data.ttdie);
			printf("debug : tteat = %ld\n", data.tteat);
			printf("debug : ttsleep = %ld\n", data.ttsleep);
			printf("debug : max meal = %ld\n\n", data.max_meal);
		}

		// 2) create things
		init_all(&data);
		
		// 3)
		start_simulation(&data);
		
		// 4) when philo is full | 1 philo died 
		//clean_all(&data);
	}
	else
	{
		error_exit("Wrong Input\n ./philo nb ttdie tteat ttsleep [max]");
	}
}