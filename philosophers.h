#include <stdio.h> // printf waiting my integration

#include <stdlib.h> // malloc, free
#include <unistd.h> // usleep
#include <stdbool.h> // boolean condition
#include <pthread.h> // mutex, threading
#include <sys/time.h> // get time of the day

typedef pthread_mutex_t t_mutex;

//** Structures **//

typedef struct s_data
{
	long	nb_philo; // av[1]
	long	ttdie;	// av[2]
	long	tteat;	// av[3]
	long	ttsleep; // av[4]
	long	max_meal; // av[5] optionnal in []
	long	simulation_date; // date when sim start
	bool	is_end; 
	t_fork	*forks; // arrray of forks
	t_philo	*philos; // array of philos

};

typedef struct s_fork
{
	t_mutex	fork;
	int	fork_id; // place of the fork IN TAB (1st one get index 0)
}	t_fork;

/* PHILO */

typedef struct s_philo
{
	int	index;	// place of the philo IN TAB (1st one get index 0)
	long	meal_counter; // varible to check max meal
	bool	isfull; // boolean indicationg if the philo ate the max meals
	long	last_meal;
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t thread_index;

}	t_philo;

