/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:23:01 by sentry            #+#    #+#             */
/*   Updated: 2024/05/17 16:46:59 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	thinking() simulates the philosopher thinking for a certain amount of time 
	before eating or sleeping.

	Flow:
	- if the philosopher number is even, fn() does nothing and returns (this is 
	because the even numbered philosophers will always take turns to just eat 
	or sleep)
	- if the philosopher number is odd, the fn() calculates the time to think 
	(from 2 x eating time - sleeping time). If the result is less than 0, it 
	is set to 0. This is so that 2 x (thinking + sleeping) = eating time in 
	order for the philos to be occupied with those actions whilst not able to 
	eat.  
	- the philo then thinks for the calculated time
*/

void	thinking(t_philo *philo)
{
	long	eating_time;
	long	sleeping_time;
	long	thinking_time;

	if (philo->data->philo_count % 2 == 0)
		return ;
	write_status(THINKING, philo, DEBUG_MODE);
	eating_time = philo->data->time_to_eat;
	sleeping_time = philo->data->time_to_sleep;
	thinking_time = eating_time * 2 - sleeping_time;
	if (thinking_time < 0)
		thinking_time = 0;
	precise_usleep(thinking_time, philo->data);
}

/*
    lone_philo() will handle the situation where there is only one philo
	using pretty much the same code as for >1 philo BUT essentially it 
	will:
	- lock the first_fork with write_status just for output 
    purposes (philo cannot eat with only one fork so it will just wait to 
	die)
    - wait by sleeping until monitor busts it and sets the sim_finish_time 
	boolean to true i.e simulation finished
*/

void	*lone_philo(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->data->access_mutex,
		&philo->data->threads_running_count);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!sim_finished(philo->data))
		usleep(200);
	return (NULL);
}

/*
    eating() simulates the philosopher eating for a certain amount of time.

	Flow:
    - fn() locks two forks (first_fork and second_fork) using safe_mutex()
	indicating that the philosopher hastaken posesssion of the forks and 
	outputs as such
	-fn() then locks the eat_die_mutex which is used to ensure that the philo
	is given exclusive access to eating
	- fn() updates last_meal_time, meal_count++, and outputs EATING 
	(last_meal_time happens before eating in order to avoid deaths while 
    a philo is eating)
	- fn() then releases eat_die_mutex(), and the fn() sleeps for a period of 
	time 
	- if the meal_limit is reached, fn() sets the full boolean to true
    - fn() then releases both forks
*/

static void	eating(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork_mutex, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex(&philo->second_fork->fork_mutex, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	safe_mutex(&philo->eat_die_mutex, LOCK);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	philo->meal_count++;
	write_status(EATING, philo, DEBUG_MODE);
	safe_mutex(&philo->eat_die_mutex, UNLOCK);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->meal_limit > 0
		&& philo->meal_count == philo->data->meal_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->first_fork->fork_mutex, UNLOCK);
	safe_mutex(&philo->second_fork->fork_mutex, UNLOCK);
}

/*
	dinner_simulation() i.e. the actual dinner simulates the dinner routine 
	where philosopher(s) are either eating, sleeping, or thinking.

	Flow:
	- the value of the philosopher argument is assigned to the philo
	variable
	- wait_all_threads() is then called to wait for all threads to be ready
	- set_long() is then called to set the last_meal_time to the current time
	(in milliseconds)
	- increase_long() is then called to increase the number of running threads
	- desynchronize_philos() is then called to desynchronize the philos 
	(for fairness)
	- an endless loop is started, while the sim is not finished or philo 
	object is not full, where: philo eats, sleeps, and thinks
*/

static void	*dinner_simulation(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->data->access_mutex,
		&philo->data->threads_running_count);
	desynchronize_philos(philo);
	while (!sim_finished(philo->data))
	{
		if (philo->full)
			break ;
		eating(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

/*
	start_dinner() orchestrates the start of the dinner simulation involving 
	multiple philos. It creates all the threads for each philo to run the fn() 
	concurrently, and then creates the monitor thread to oversee the 
	simulation.

	Flow:
	- if meal_limit == 0, fn() returns
	- if only 1 philo, fn() creates 1 thread, and runs lone_philo()
	- else fn() creates all the philos
	- fn() then creates the monitor thread to search for deaths
	- sim_start_time is set 
	- all_threads_ready is set to true and a thread is created for each philo,
	with the thread_id stored in the data->philos_arr[i].thread_id field
	- JOIN is used to wait for each philo's thread to finish its execution
	before going to the next iteration
	- after the loop, safe_thread() is called again to create the monitor 
	thread which manages the dinner simulation (JOIN is again used to wait 
	for the monitor's thread to finish its execution)
*/

void	start_dinner(t_data	*data)
{
	int	i;

	i = -1;
	if (data->meal_limit == 0)
		return ;
	else if (data->philo_count == 1)
		safe_thread(&data->philos_arr[0].thread_id, lone_philo,
			&data->philos_arr[0], CREATE);
	else
	{
		while (++i < data->philo_count)
			safe_thread(&data->philos_arr[i].thread_id, dinner_simulation,
				&data->philos_arr[i], CREATE);
	}
	safe_thread(&data->monitor, monitor_dinner, data, CREATE);
	data->sim_start_time = get_time(MILLISECOND);
	set_bool(&data->access_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->philo_count)
		safe_thread(&data->philos_arr[i++].thread_id, NULL, NULL, JOIN);
	safe_thread(&data->monitor, NULL, NULL, JOIN);
}
