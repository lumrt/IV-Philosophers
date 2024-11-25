#include <stdio.h> // printf waiting my integration

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>

# define DEBUG_MODE 0

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
} t_flags ;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FIRST_FORK,
	TAKING_SECOND_FORK,
	DIED,
}	t_philo_status;

//** Structures **//

typedef struct s_fork
{
	t_mutex	fork;
	int	fork_id; // place of the fork IN TAB (1st one get index 0)
}	t_fork;

typedef struct s_philo
{
	int	index;	// place of the philo IN TAB (1st one get index 0)
	long	meal_counter; // varible to check max meal
	bool	isfull; // boolean indicationg if the philo ate the max meals
	long	last_meal;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_mutex	philo_mtx; // useful races with monitor
	pthread_t	thread_index;

	t_mutex	*start_mtx;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	long	nb_philo; // av[1]
	long	ttdie;	// av[2]
	long	tteat;	// av[3]
	long	ttsleep; // av[4]
	long	max_meal; // av[5] optionnal in []
	long	simulation_date; // date when sim start
	bool	is_end; 
	bool	trheads_sync; 
	long	nb_thread_run;
	pthread_t monitor; //
	t_mutex variable_mtx; // avoid datarace on booleans and variables
	t_mutex	write_mtx; 
	t_mutex	start_mtx;
	t_fork	*forks; // arrray of forks
	t_philo	*philos; // array of philos
	int	debug_mode;

}	t_data;


/* PHILO */


//////////// TOOLS.c /////////////

void    error_exit(char *err_str);
long	gettime(t_time_code time_code);
void	sharper_usleep(long usec, t_data *data);
void    write_status(t_philo_status status, t_philo *philo, bool debug);

/////////// PARSING.c ////////////

void    parsing(t_data *data, char **av);

////////// WRAPPER.c ////////////

void	safe_mutex_handler(t_mutex *mtx, t_flags flag);
void	safe_thread_handler(pthread_t *thread, void *(*foo)(void *), void *data, t_flags flag);

////////// DATA.C ///////////////

void    init_all(t_data *data);

///////// GET SET.c /////////////

void	set_b(t_mutex *mtx, bool *dst, bool value);
bool	get_b(t_mutex *mtx, bool *value);
void	set_l(t_mutex *mtx, long *dst, long value);
long	get_l(t_mutex *mtx, long *value);
bool	sim_finish(t_data *data);

//////// SYNCHRO.c //////////////

void   sync_threads(t_data *data);
bool    all_running(t_mutex *mutex, long *threads, long nb_philo);
void    increase_l(t_mutex *mtx, long *value);

//////// SIMULATION.c ///////////

void    starting_simulation(t_data *data);
void    *starting_dinner(void *data);

/////// MONITORING.c ///////////

int    monitor_dinner(t_data* data);