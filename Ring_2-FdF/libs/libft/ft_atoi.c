/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:16 by atang             #+#    #+#             */
/*   Updated: 2023/07/21 11:15:25 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     atoi -- convert ASCII string to integer

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <stdlib.h>

     int
     atoi(const char *str);

     #include <xlocale.h>

     int
     atoi_l(const char *str, locale_t loc);

DESCRIPTION
     The atoi() function converts the initial portion of the string pointed 
	 to by str to int representation.

     It is equivalent to:

           (int)strtol(str, (char **)NULL, 10);
 */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

/* 
int	main(void)
{
	const char	str[] = " -12345";
	int			num = ft_atoi(str);

	printf ("%d\n", num);
	return (0);
}
 */