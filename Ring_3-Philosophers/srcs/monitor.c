/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:54:55 by sentry            #+#    #+#             */
/*   Updated: 2024/05/11 22:48:29 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	philo_died() is a bool that checks if the philosopher has died.

	Flow:
	- fn() checks if the philosopher is full, he has already finished his 
	own simulation. Monitor does not care. Return.
	- fn() checks if the philosopher is dead by reading in a thread safe manner 
	the last_meal time. Acquire the lock on the eat_die_mutex to prevent
	multiple threads from checking the last_meal_time simultaneously
	- fn() calculates the elapsed time since the philosopher last ate using the 
	current time and the last_meal_time
	- time_to_die in converted from microseconds to milliseconds
	- fn() checks if the elapsed time is greater than the time_to_die, if so 
	return true indicating the philosopher is dead
	- fn() releases the lock on the eat_die_mutex since we are done checking the 
	last_meal_time
	- fn() returns false indicating the philosopher is still alive
*/

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	safe_mutex(&philo->eat_die_mutex, LOCK);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->data->time_to_die / 1e3;
	if (elapsed > time_to_die)
	{
		write_status(DIED, philo, DEBUG_MODE);
		safe_mutex(&philo->eat_die_mutex, UNLOCK);
		return (true);
	}
	safe_mutex(&philo->eat_die_mutex, UNLOCK);
	return (false);
}

/*
	all_full() is a bool that checks if all philos are full by iterating
	through the philos array and checking if the full field is true. It 
	returns flase if any philo is not full otherwise it sets the flag to
	indicate all philos are full and returrns true. 
*/

static bool	all_full(t_philo *philos, long philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
		if (philos[i].full == false)
			return (false);
	set_bool(&philos->data->access_mutex, &philos->data->all_philos_full, true);
	return (true);
}

/*
	monitor_dinner() is a thread that continuously monitors for any dead philos
	or if all of them are full.
  
	Flow:
	- fn() checks if the all_threads_running
	- fn() checks if any philos died -> sets flag to end simulation if so
	- fn() checks if all philos are full -> also sets flag to end simulation
*/

void	*monitor_dinner(void *ph_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)ph_data;
	while (!all_threads_running(&data->access_mutex,
			&data->threads_running_count, data->philo_count))
		;
	while (!sim_finished(data))
	{
		i = -1;
		while (++i < data->philo_count && !sim_finished(data))
		{
			if (philo_died(data->philos_arr + i))
				set_bool(&data->access_mutex, &data->sim_finish_time, true);
			else if (all_full(data->philos_arr, data->philo_count))
			{
				set_bool(&data->access_mutex, &data->sim_finish_time, true);
				write_status(FULL, data->philos_arr + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
