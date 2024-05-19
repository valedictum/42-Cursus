/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:47:08 by sentry            #+#    #+#             */
/*   Updated: 2024/05/17 12:25:57 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Same as write_status, just with more information to help when debugging 
	(i.e. DEBUG_MODE = 1)
*/

static void	write_status_debug(t_philo_status status, t_philo *philo,
	long elapsed)
{
	if (TAKE_FIRST_FORK == status && !sim_finished(philo->data))
		printf(W"%-6ld"RST" %d has taken a FIRST fork\n"
			"\t\t\t"B"🍴 #%d\n"RST, elapsed, philo->philo_id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !sim_finished(philo->data))
		printf(W"%-6ld"RST" %d has taken a SECOND fork\n"
			"\t\t\t"B"🍴 #%d\n"RST, elapsed, philo->philo_id,
			philo->second_fork->fork_id);
	else if (EATING == status && !sim_finished(philo->data))
		printf(W"%-6ld"G" %d is eating\n"
			"\t\t🍝 #%ld\n"RST, elapsed, philo->philo_id, philo->meal_count);
	else if (SLEEPING == status && !sim_finished(philo->data))
		printf(W"%-6ld"B" %d is sleeping\n"RST, elapsed, philo->philo_id);
	else if (THINKING == status && !sim_finished(philo->data))
		printf(W"%-6ld"Y" %d is thinking\n"RST, elapsed, philo->philo_id);
	else if (DIED == status)
		printf(RED"%-6ld %d died 💀\n"RST, elapsed, philo->philo_id);
}

/*
    write_status() writes the philo status to standard output in a 
	threadsafe manner

	Flow:
	- get_time is used to calculate elapsed time (in milliseconds)
	- get_bool is used to check if the philo is full, if so it returns
	- write_mutex is locked
	- if debug, write_status_debug is called, otherwise fn() checks the 
	value of status and prints a corresponding message to the console using 
	printf
	- write_mutex is unlocked
*/

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->data->sim_start_time;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex(&philo->data->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !sim_finished(philo->data))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed,
				philo->philo_id);
		else if (EATING == status && !sim_finished(philo->data))
			printf(W"%-6ld"G" %d is eating\n"RST, elapsed, philo->philo_id);
		else if (SLEEPING == status && !sim_finished(philo->data))
			printf(W"%-6ld"B" %d is sleeping\n"RST, elapsed, philo->philo_id);
		else if (THINKING == status && !sim_finished(philo->data))
			printf(W"%-6ld"Y" %d is thinking\n"RST, elapsed, philo->philo_id);
		else if (DIED == status)
			printf(W"%-6ld"RED" %d died\n"RST, elapsed, philo->philo_id);
	}
	safe_mutex(&philo->data->write_mutex, UNLOCK);
}
