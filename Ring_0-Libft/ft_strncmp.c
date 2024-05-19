/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:35:31 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 17:11:50 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     strcmp, strncmp -- compare strings

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     int
     strcmp(const char *s1, const char *s2);

     int
     strncmp(const char *s1, const char *s2, size_t n);

DESCRIPTION
     The strcmp() and strncmp() functions lexicographically compare the 
	 null-terminated strings s1 and s2.

     The strncmp() function compares not more than n characters.  Because 
	 strncmp() is designed for comparing strings rather than binary data, 
	 characters that appear after a `\0' character are not compared.

RETURN VALUES
     The strcmp() and strncmp() functions return an integer greater than, 
	 equal to, or less than 0, according as the string s1 is greater than, 
	 equal to, or less than the string s2.  The comparison is done using 
	 unsigned characters, so that `\200' is greater than `\0'.
 */
/*
	- the function returns a negative value if s1 is "less than" s2, 
	a positive value if s1 is "greater than" s2
	- unsigned char to ensure correct behavior during comparison, 
	specifically with negative values
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n > 0)
	{
		if (*s1 != *s2)
		{
			u1 = (unsigned char)*s1;
			u2 = (unsigned char)*s2;
			return (u1 - u2);
		}
		if (*s1 == '\0' && *s2 == '\0')
		{
			break ;
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

/* 
int	main(void)
{
	const char	*str1 = "Outcome";
	const char	*str2 = "Outdoor";
	size_t	nbr = 4;
	int	result = ft_strncmp(str1, str2, nbr);

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
}

 */
