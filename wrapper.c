/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:08 by lucas             #+#    #+#             */
/*   Updated: 2024/09/07 18:20:37 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


 // MUTEX WRAPPER//

static void	handle_mtx_error(int status, t_flags flag)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (flag == UNLOCK || flag == LOCK))
		error_exit("check man mutex_lock for better error");
	else if (status == EINVAL && flag == INIT)
		error_exit("check man mutex_inits for better error");
	else if (status == EDEADLK)
		error_exit("deadlock would occure if the thread blocked wtng for mutex");
	else if (status == ENOMEM)
		error_exit("check man mutex_inits for better error");
	else if (status == EBUSY)
		error_exit("check man mutex_inits for better error");

}

void    safe_mutex_handler(t_mutex *mtx, t_flags flag)
{
	if (flag == LOCK)
		handle_mtx_error(pthread_mutex_lock(mtx), flag);
	else if (flag == UNLOCK)
		handle_mtx_error(pthread_mutex_unlock(mtx), flag);
	else if (flag == INIT)
		handle_mtx_error(pthread_mutex_init(mtx, NULL), flag);
	else if (flag == DESTROY)
		handle_mtx_error(pthread_mutex_destroy(mtx), flag);
	else
		error_exit("Wrong flag for mutex\n");
}

// THREADS WRAPPER

// static void	handle_thread_error(int status, t_flags flag)
// {

// }

// void	safe_thread_handler(pthread_t *thread, void *(*foo)(void *),
// 		 void *data, t_flags flag)
// {
	
// }