/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:02:38 by atang             #+#    #+#             */
/*   Updated: 2024/04/28 08:27:17 by sentry           ###   ########.fr       */
/*                                        
                                    */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> // write, usleep
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <limits.h>
# include <stdbool.h> 
# include <pthread.h> // mutex: init, destroy, lock, unlock 
//+ threads: create, join, detach
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX
# include <errno.h>

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage: 
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** RST to reset the color after setting it.
*/

# define RST    "\033[0m"      /* Reset to default color */
# define RED    "\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

// Write fn() MACRO
# define DEBUG_MODE 0

// PHILO MAX - by default is 200
# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

// PHILO STATES
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
	FULL,
}			t_philo_status;

// OPCODE for mutex | thread fns()
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

// CODES for gettime
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef pthread_mutex_t	t_mtx;

// IOU FOR COMPILER//
typedef struct s_data	t_data;

// FORK //
typedef struct s_fork
{
	t_mtx	fork_mutex;
	int		fork_id;
}				t_fork;

// PHILO //
typedef struct s_philo
{
	int			philo_id;
	long		meal_count;
	bool		full;
	long		last_meal_time; // time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; // a philo is a thread
	t_mtx		philo_mutex; // useful for races with the monitor
	t_mtx		eat_die_mutex;
	pthread_t	monitor;
	t_data		*data;
}				t_philo;

// DATA //
struct s_data
{
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meal_limit; // [5] optional | FLAG if -1
	long		sim_start_time; // time
	bool		sim_finish_time; // when a philo dies | all philos are full
	long		threads_running_count;
	pthread_t	monitor;
	bool		all_threads_ready; // synchro philos
	t_mtx		access_mutex; // avoid races while reading from data
	t_mtx		write_mutex;
	bool		all_philos_full;
	t_fork		*forks_arr; // array of forks
	t_philo		*philos_arr; // array of philos
};

// dinner.c //
void	thinking(t_philo *philo);
void	start_dinner(t_data *data);

// init.c //
void	init_data(t_data *data);

// safe.c //
void	*safe_malloc(size_t bytes);
void	safe_mutex(t_mtx *mutex, t_opcode opcode);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

// getters_setters.c // 

void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	sim_finished(t_data *data);

// synchro_utils.c //
void	wait_all_threads(t_data *data);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_num);
void	increase_long(t_mtx *mutex, long *value);
void	desynchronize_philos(t_philo *philo);

// monitor.c //
void	*monitor_dinner(void *data);

// parse.c //
void	parse_input(t_data *data, char **argv);

// utils.c //
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_data *data);
void	clean(t_data *data);
void	error_exit(const char	*error_msg);
void	debug(const char *msg);

// write.c //
void	write_status(t_philo_status status, t_philo *philo, bool debug);

#endif