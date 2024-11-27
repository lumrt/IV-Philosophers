/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:43:32 by lucas             #+#    #+#             */
/*   Updated: 2024/11/27 17:39:02 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_data	t_data;

// ** ENUMS **//

typedef enum e_flags
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_flags;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FIRST_FORK,
	TAKING_SECOND_FORK,
	DIED,
}						t_philo_status;

//** Structures **//

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	long				meal_counter;
	long				last_meal;
	bool				isfull;
	int					index;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_mutex				philo_mtx;
	t_mutex				*start_mtx;
	t_data				*data;
	pthread_t			thread_index;
}						t_philo;

typedef struct s_data
{
	long				nb_philo;
	long				ttdie;
	long				tteat;
	long				ttsleep;
	long				max_meal;
	long				simulation_date;
	bool				is_end;
	bool				trheads_sync;
	long				nb_thread_run;
	t_mutex				variable_mtx;
	t_mutex				write_mtx;
	t_mutex				start_mtx;
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			monitor;
}						t_data;

/* PHILO */

//////////// TOOLS.c /////////////

void					error_exit(char *err_str);
long					gettime(t_time_code time_code);
void					sharper_usleep(long usec, t_data *data);
void					write_status(t_philo_status status, t_philo *philo);

/////////// PARSING.c ////////////

void					parsing(t_data *data, char **av);

////////// WRAPPER.c ////////////

void					safe_mutex_handler(t_mutex *mtx, t_flags flag);
void					safe_thread_handler(pthread_t *thread,
							void *(*foo)(void *), void *data, t_flags flag);

////////// DATA.C ///////////////

void					init_all(t_data *data);
void					free_all(t_data *data);

///////// GET SET.c /////////////

void					set_b(t_mutex *mtx, bool *dst, bool value);
bool					get_b(t_mutex *mtx, bool *value);
void					set_l(t_mutex *mtx, long *dst, long value);
long					get_l(t_mutex *mtx, long *value);
bool					sim_finish(t_data *data);

//////// SYNCHRO.c //////////////

void					sync_threads(t_data *data);
bool					all_running(t_mutex *mutex, long *threads,
							long nb_philo);
void					increase_l(t_mutex *mtx, long *value);

//////// SIMULATION.c ///////////

void					starting_simulation(t_data *data);
void					*starting_dinner(void *data);
void					*ft_alone(void *arg);

/////// MONITORING.c ///////////

int						monitor_dinner(t_data *data);

#endif