/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:46:22 by atang             #+#    #+#             */
/*   Updated: 2024/05/11 23:03:11 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	get_time() returns the current time in different units (seconds, 
	milliseconds, or microseconds) based on the input parameter time_code.
	It uses gettimeofday() to get the current time and performs 
	some calculations to convert it to the desired unit. If the time_code is 
	not valid, it exits with an error message.
*/

long	get_time(t_time_code time_code)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (current_time.tv_sec + (current_time.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((current_time.tv_sec * 1e6) + current_time.tv_usec);
	else
		error_exit("Wrong input to gettime:"
			"use <MILLISECOND> <MICROSECOND> <SECONDS>");
	return (1337);
}

/*
	precise_usleep() pauses the execution for a specified time period 
	in microseconds. It uses a hybrid approach of usleep and spinlock 
	to ensure precise timing. It checks if the simulation is finished 
	and adjusts the sleep duration to achieve the desired precision.

	Flow:
	- fn() gets the current time in microseconds
	- while the elapsed time is less than the desired pause time:
		a. check if the simulation is finished
		b. calculate the elapsed time and remaining time
		c. if the remaining time is greater than 1000us, usleep for half
		the remaining time.
		d. otherwise, spinlock for the remaining time.
		(this is done to minimise the time spent in usleep; usleep is not 
		very precise and can sleep for longer than the desired amount of time.
		Spinlocking for a short period of time is almost as fast as usleeping 
		for the same amount of time...basically the total time spent sleeping 
		is minimised.
	- when the desired pause time is reached, exit the loop
*/

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (sim_finished(data))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

/*
	clean() is the clean up fn() that releases resources used by the program.
	It destroys mutexes and frees memory allocated for the forks and 
	philosophers before freeeing the forks array and philosophers array. 
	It is called at the end of the simulation.
*/

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_count)
	{
		philo = data->philos_arr + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
		safe_mutex(&philo->eat_die_mutex, DESTROY);
	}
	safe_mutex(&data->write_mutex, DESTROY);
	safe_mutex(&data->access_mutex, DESTROY);
	free(data->forks_arr);
	free(data->philos_arr);
}
/*
	error_exit() prints a custom error message and exit
 	R->RED
	RST->RESET
*/

void	error_exit(const char	*error_msg)
{
	printf(RED"%s\n"RST, error_msg);
	exit(EXIT_FAILURE);
}

/*
	Custom debug function
*/

void	debug(const char *msg)
{
	printf(C"%s\n"RST, msg);
}
