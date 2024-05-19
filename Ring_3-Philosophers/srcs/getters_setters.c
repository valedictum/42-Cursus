/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:35:10 by sentry            #+#    #+#             */
/*   Updated: 2024/05/11 21:57:52 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Contains getters and setters to avoid writing LOCK UNLOCK everywhere.
    Have only used longs and bools as you only need to use 2 types of setters 
    and getters.
*/

/*
	set_bool() safely sets a boolean value value to the memory location pointed 
	by dest using a mutex to ensure thread safety.
*/

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

/*
	get_bool() safely retrieves the boolean value stored in the memory 
	location pointed to by value while using a mutex to ensure thread safety.
*/

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

/*
	get_long() safely retrieve the value of a long variable while 
	ensuring thread safety by using a mutex.
*/

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

/*
	set_long() safely sets the value of dest to value, while 
	ensuring thread safety by using a mutex. It does this by 
	locking the mutex using safe_mutex(mutex, LOCK), setting 
	the value of dest to value, and then unlocking the mutex 
	using safe_mutex(mutex, UNLOCK).
*/

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

/*
	sim_finished() uses get_bool() to safely retrieve the value 
	of sim_finish_time (it locks the mutex, retrieves the value 
	of the boolean variable, and then unlocks the mutex.)
*/

bool	sim_finished(t_data *data)
{
	return (get_bool(&data->access_mutex, &data->sim_finish_time));
}
