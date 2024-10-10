/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:45:20 by lucas             #+#    #+#             */
/*   Updated: 2024/10/10 12:08:55 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


long	gettime(t_time_code time_code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday Failed !");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input for Gettime");
	return (42);
	
}

// gettimeofday sharper

void	sharper_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;
	
	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (sim_finish(data))
			break;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(usec / 2);
		else
		{
			// SPINLOCK
			while (gettime(MICROSECOND) - start < usec)
			;
		}
	}
}

void    error_exit(char *err_str)
{
	printf("%s", err_str); // change by my integration
	exit(EXIT_FAILURE);
}
