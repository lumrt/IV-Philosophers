#include <stdio.h> // printf waiting my integration

#include <stdlib.h> // malloc, free
#include <unistd.h> // usleep
#include <stdbool.h> // boolean condition
#include <limits.h> // INTMAX
#include <pthread.h> // mutex, threading
#include <sys/time.h> // get time of the day
#include <errno.h> // better error handling espacially for mutexes

typedef pthread_mutex_t	t_mutex; // avoid line_too_long

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
	pthread_t	thread_index;
	pthread_t	monitoring;
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
	t_mutex variable_mtx; // avoid datarace on booleans and variables
	t_fork	*forks; // arrray of forks
	t_philo	*philos; // array of philos
	int	debug_mode;

}	t_data;


/* PHILO */


//////////// TOOLS.c /////////////

void    error_exit(char *err_str);

/////////// PARSING.c ////////////

void    parsing(t_data *data, char **av);

////////// WRAPPER.c ////////////

void    safe_malloc_handle(size_t bytes);
void	safe_mutex_handler(t_mutex *mtx, t_flags flag);
void	safe_thread_handler(); //TODO

////////// DATA.C ///////////////

void    init_all(t_data *data);