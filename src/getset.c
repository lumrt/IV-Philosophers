/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:58:52 by lucas             #+#    #+#             */
/*   Updated: 2024/11/27 15:58:02 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_b(t_mutex *mtx, bool *dst, bool value)
{
	safe_mutex_handler(mtx, LOCK);
	*dst = value;
	safe_mutex_handler(mtx, UNLOCK);
}

bool	get_b(t_mutex *mtx, bool *value)
{
	bool	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value ;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

void	set_l(t_mutex *mtx, long *dst, long value)
{
	safe_mutex_handler(mtx, LOCK);
	*dst = value;
	safe_mutex_handler(mtx, UNLOCK);
}

long	get_l(t_mutex *mtx, long *value)
{
	long	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

bool	sim_finish(t_data *data)
{
	return (get_b(&data->variable_mtx, &data->is_end));
}
