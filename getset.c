/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:58:52 by lucas             #+#    #+#             */
/*   Updated: 2024/10/10 11:53:39 by lucas            ###   ########.fr       */
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

void	get_l(t_mutex *mtx, long *dst, long value)
{
	safe_mutex_handler(mtx, LOCK);
	*dst = value;
	safe_mutex_handler(mtx, UNLOCK);
}
bool	sim_finish(t_data *data)
{
	return (get_b(&data->variable_mtx, &data->is_end));
}