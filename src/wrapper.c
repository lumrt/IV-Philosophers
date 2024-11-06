/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:57:08 by lucas             #+#    #+#             */
/*   Updated: 2024/11/06 17:16:20 by lumaret          ###   ########.fr       */
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
	int	status;

	if (flag == LOCK)
	{
		status = pthread_mutex_lock(mtx);
		handle_mtx_error(status, flag);
	}
	else if (flag == UNLOCK)
	{
		status = pthread_mutex_unlock(mtx);
		handle_mtx_error(status, flag);
	}
	else if (flag == INIT)
	{
		status = pthread_mutex_init(mtx, NULL);
		handle_mtx_error(status, flag);
	}
	else if (flag == DESTROY)
	{
		status = pthread_mutex_destroy(mtx);
		handle_mtx_error(status, flag);
	}
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
	else if (status == EINVAL && (flag == JOIN || flag == DETACH))
		error_exit("the value specified by thread is not joinable");
	else if (status == ESRCH)
	{
		// printf("%d\n", flag);
		error_exit("No thread could be fond by this ID\n");
	}
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