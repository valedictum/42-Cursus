/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 07:46:30 by sentry            #+#    #+#             */
/*   Updated: 2024/05/11 16:20:08 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Every philo is assigned a first and second fork. It is
    EVEN and ODD fork assignment (not L and R) to avoid deadlock.

	assign_forks() assigns the first and second forks to a philo (t_philo) based
	on their position and id (NO return value) to avoid deadlocks by making sure 
	not all philos are picking up their forks in the same order.

	Inputs:
	philo - a ptr to a t_philo struct (i.e. a philo)
	forks_arr - an array of t_fork structs representing available forks
	philo_position - int representing the position of the philo in the array

	Flow:
	- philo_count retrieved
	- FIRST fork is assigned to the philo as the next fork 
	in the array (R)
	- SECOND fork is assigned to the philo as the current fork 
	in the array (L)
	- IF the philo_id is even, the first and second forks are swapped so that 
	the even philos always pick up the left fork first (L = current in array, 
	R = next in array)
*/

static void	assign_forks(t_philo *philo, t_fork *forks_arr, int philo_position)
{
	int	philo_count;

	philo_count = philo->data->philo_count;
	philo->first_fork = &forks_arr[(philo_position + 1) % philo_count];
	philo->second_fork = &forks_arr[philo_position];
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &forks_arr[philo_position];
		philo->second_fork = &forks_arr[(philo_position + 1) % philo_count];
	}
}

/*
    init_philo() initialises all the t_philo structs (i.e the philosophers)
	with the necessary fields.

	Inputs:
	data - a ptr to a t_data structure called data

	Flow:
	- iterating over each t_philo struct in the philos array, for each structure 
	it initialises the philo_id, full and meal_count fields
	- the data ptr is assigned to the data field of the t_philo struct
	- philo_mutex and eat_die_mutex are initiliased using safe_mutex()
	- assign_forks() is called to assigned the first and second forks to the 
	t_philo struct
*/

static void	init_philo(t_data *data)
{
	int			i;
	t_philo		*philo;

	i = -1;
	while (++i < data->philo_count)
	{
		philo = data->philos_arr + i;
		philo->philo_id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->data = data;
		safe_mutex(&philo->philo_mutex, INIT);
		safe_mutex(&philo->eat_die_mutex, INIT);
		assign_forks(philo, data->forks_arr, i);
		if (DEBUG_MODE == 1)
			printf("philo %d created\n", data->philos_arr[i].philo_id);
	}
}

/*
	init_data() initialises the t_data data structure with all the necessary 
	fields (NO return value).

	Inputs:
	data - a ptr to a t_data structure called data

	Flow:
	- the bools sim_finish_time and all_threads_ready are initialised to false,
	and threads_running_count is initialised to 0
	- memory is dynamically allocated for an array for philos with the ptr 
	assigned to data->philos_arr
	- access_mutex and write_mutex are initialised using safe_mutex()
	- memory is dynamically allocated for an array for forks with the ptr
	assigned to data->forks_arr
	- fork_mutexes are initialised over the data->philo_count using safe_mutex()
	and unique forks_ids are assigned to each t_fork struct
	- init_philo() is then called to initiliased the t_philo structs
*/

void	init_data(t_data	*data)
{
	int	i;

	i = -1;
	data->sim_finish_time = false;
	data->all_threads_ready = false;
	data->threads_running_count = 0;
	data->philos_arr = safe_malloc(data->philo_count * sizeof(t_philo));
	safe_mutex(&data->access_mutex, INIT);
	safe_mutex(&data->write_mutex, INIT);
	data->forks_arr = safe_malloc(data->philo_count * sizeof(t_fork));
	while (++i < data->philo_count)
	{
		safe_mutex(&data->forks_arr[i].fork_mutex, INIT);
		data->forks_arr[i].fork_id = i;
		if (DEBUG_MODE == 1)
			printf("fork %d created\n", data->forks_arr[i].fork_id);
	}
	init_philo(data);
}
