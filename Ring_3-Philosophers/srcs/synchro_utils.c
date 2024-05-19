/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:51:47 by sentry            #+#    #+#             */
/*   Updated: 2024/05/11 21:45:07 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	wait_all_threads() waits until all threads are ready to synchronise philos 
	start. It does this via a spinlock mechanism (where a thread attempts to 
	acquire a lock by continuously (in a loop) checking a shared variable 
	until it becomes available) to check the value of boolean 
	variable data->all_threads_ready by calling the get_bool function with 
	&data->access_mutex and &data->all_threads_ready as arguments. 
	The function loops until the value of data->all_threads_ready becomes true.
*/

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->access_mutex, &data->all_threads_ready))
		;
}

/*
	all_threads_running() checks if all threads are running by comparing the
	value of the variable 'threads' to the total number of philosophers.

	Flow:
	- fn() first acquires a lock on the mutex 'mutex' to ensure that 
	multiple threads do not access the variable 'threads' at the same time
	- once the lock is acquired, fn() checks if the value of 'threads' is
	equal to the number of philosophers 'philo_count'. If it is, the function
	sets the return value to true. Otherwise, it sets the return value to 
	false
	- fn() unlocks the mutex to allow other threads to access the variable 
	'threads'
*/

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_count)
{
	bool	ret;

	ret = false;
	safe_mutex(mutex, LOCK);
	if (*threads == philo_count)
		ret = true;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

/*
    increase_long() increases threads running to synchronise with the 
	monitor i.e. when a philo enters the loop, thread_count++
*/

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}

/*
    desynchronize_philos() is used to desynchronise the philos 
	to minimise resource contention and improve fairness
    1) if philo_count is even and philo_id is even, start by 
	sleeping for 30000 microseconds
    2) if odd, start by thinking
*/

// can static this if needed like Thuy
void	desynchronize_philos(t_philo *philo)
{
	if (philo->data->philo_count % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			precise_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->philo_id % 2 == 0)
			thinking(philo);
	}
}
