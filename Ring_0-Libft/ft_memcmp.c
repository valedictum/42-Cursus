/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:10:17 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 16:55:07 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     memcmp -- compare byte string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     int
     memcmp(const void *s1, const void *s2, size_t n);

DESCRIPTION
     The memcmp() function compares byte string s1 against byte string s2.  
	 Both strings are assumed to be n bytes long.

RETURN VALUES
     The memcmp() function returns zero if the two strings are identical, 
	 otherwise returns the difference between the first two differing bytes 
	 (treated as unsigned char values, so that `\200' is greater than `\0', 
	 for example).  Zero-length strings are always identical.  This behavior is
	 not required by C and portable code should only depend on the sign of 
	 the returned value.
 */
/* 
	- if the returned value is negative, it means s1 is less than s2
	- if the returned value is positive, it means s1 is greater than s2	
 */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		else
			i++;
	}
	return (0);
}

/* int	main(void)
{
	const char	*str1 = "Outcome";
	const char	*str2 = "Outdoor";
	size_t	nbr = 6;
	int	result = ft_memcmp(str1, str2, nbr);

	printf("String 1: %s\n", str1);
	printf("String 2: %s\n", str2);
	printf("Number: %zu\n", nbr);
	if (result == 0)
	{
		printf("String 1 is equal to String 2.\n");
	}
	else if (result > 0)
	{
		printf("String 1 is greater than String 2.\n");
	}
	else
	{
		printf("String 1 is less than String 2.\n");
	}
	return (0);
} */
