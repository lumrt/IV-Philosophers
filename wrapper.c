/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:08 by lucas             #+#    #+#             */
/*   Updated: 2024/09/08 17:48:38 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


 // MUTEX WRAPPER //

static void	handle_mtx_error(int status, t_flags flag)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (flag == UNLOCK || flag == LOCK))
		error_exit("Value specified by mutex is invalid");
	else if (status == EINVAL && flag == INIT)
		error_exit("Value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("deadlock would occure if the thread blocked wtng for mutex");
	else if (status == ENOMEM)
		error_exit("The process can't allocate enough memory to create a thread");
	else if (status == EBUSY)
		error_exit("Mutex is locked");

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

// THREADS WRAPPER //

static void	handle_thread_error(int status, t_flags flag)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No ressources to create another thread");
	else if (status == EPERM)
		error_exit("Caller does not have correct permissions");
	else if (status == EINVAL && flag == CREATE)
		error_exit("Value specified by attr is invalid");
	else if (status == EINVAL && (flag == JOIN || flag - DETACH))
		error_exit("the value specified by thread is not joinable");
	else if (status == ESRCH)
		error_exit("No thread could be fond by this ID");
	else if (status == EDEADLK)
		error_exit("Deadlock was detected on the thread");
}

void	safe_thread_handler(pthread_t *thread, void *(*foo)(void *),
		 void *data, t_flags flag)
{
	if (flag == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), flag);
	else if (flag == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), flag);
	else if (flag == DETACH)
		handle_thread_error(pthread_detach(*thread), flag);
	else
		error_exit("Wrong flag for thread pls use <CREATE> <JOIN> <DETACH>");
}			