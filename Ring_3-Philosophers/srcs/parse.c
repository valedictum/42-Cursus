/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:12:22 by sentry            #+#    #+#             */
/*   Updated: 2024/05/11 22:54:43 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	A static inline bool that checks if the character is a digit. If the 
	character is between 0 and 9, it'll return true...otherwise it'll return 
	false (if the character is NOT a digit).
*/

static	inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
	A static inline bool that checks if the character is a space character. If 
	it is between 9 and 13 (horizontal and vertical tabs, new line, form feed 
	or carriage return OR == 32 (which is space), it'll return true...otherwise 
	it'll return false (if the character is NOT a whitespace character).
*/

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/*
	valid_input() takes a string as input and returns a pointer to the first 
	character of a valid number within the string

	Input:	
	str - a ptr to a string

	Flow: 
	- whitespace characters are skipped, as is '+'
	- only positive numbers are allowed so if the first non-whitespace 
	character is '-', or if the character is NOT a digit -> error_exit()
	- number ptr is then set to the current position in the string
	- str++ until non-digit is reached, counting with len
	- if len > 10 digits -> error_exit()
	- number ptr is returned which points to the first character of a 
	valid number within the string 
*/
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Positive values only!");
	if (!is_digit(*str))
		error_exit("The input is not a valid digit!");
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is too large, INT_MAX is the limit");
	return (number);
}

/*
	ft_atol() converts a string to a long integer.

	Input:	
	str - a ptr to a string that needs to be converted

	Flow: 
	- valid_input check
	- inside a while loop, current value is x 10 and the numerical 
	value of the current digit character is added
	- if the resultant num > INT_MAX -> error_exit()
	- converted long integer returned
*/

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("Value is too large, INT_MAX is the limit");
	return (num);
}

/*
	parse_input() takes a t_data struct ptr and argv as inputs to parse
	the input arguments and assigns the values to the corresponding 
	fields in the t_data struct. 

	Inputs:
	data - a ptr to a t_data struct
	argv

	Flow:
	- argv[1] assigned to philo_count (after conversion to long int)
	- if philo_count > 200 (PHILO_MAX) -> error_exit()
	- argv[2] assigned to time_to die field in data struct
	- argv[3] assigned to time_to eat field in data struct
	- argv[4] assigned to time_to sleep field in data struct
	- these 3 are all assigned after conversion to long int and x 1000
	(as usleep works in MICROseconds but input is in MILLIseconds)
	- if any of the time values are < the minimum 60000 (60 MILLIseconds) 
	then -> error_exit()
	- optional arg [5] in converted, multiplied, and assigned to meal_limit 
	field of data struct if it exists (if no argv[5], it is assigned -1 
	to indicate NO meal_limit)
*/

void	parse_input(t_data *data, char **argv)
{
	data->philo_count = ft_atol(argv[1]);
	if (data->philo_count > PHILO_MAX)
	{
		printf(RED"Maximum number of philosophers cannnot exceed 200"RST);
		exit(EXIT_FAILURE);
	}
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		error_exit("Use timestamps > 60ms for TTDIE, TTEAT, TTSLEEP");
	if (argv[5])
		data->meal_limit = ft_atol(argv[5]);
	else
		data->meal_limit = -1;
}
