/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:25:16 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 17:19:10 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     strchr, strrchr -- locate character in string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     char *
     strchr(const char *s, int c);

     char *
     strrchr(const char *s, int c);

DESCRIPTION
     The strchr() function locates the first occurrence of c (converted to 
	 a char) in the string pointed to by s.  The terminating null character 
	 is considered to be part of the string; therefore if c is `\0', the 
	 functions locate the terminating `\0'.

     The strrchr() function is identical to strchr(), except it locates the 
	 last occurrence of c.

RETURN VALUES
     The functions strchr() and strrchr() return a pointer to the located 
	 character, or NULL if the character does not appear in the string.
*/
/*
	- return ((char *)s); returns the address of the null terminator 
	(cast to char *)
	- (*s == (char)c) checks if the null terminator matches the target 
	character (c)
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}

/* int	main(void)
{
	const char	*str = "Hello, World!";
	char		ch = 'l';
	char		*ptr = ft_strchr(str, ch);

	printf("String: %s\n", str);
	if (ptr != NULL)
	{
		printf("First character '%c' found at: %ld\n", *ptr, ptr - str + 1);
	}
	else
	{
		printf("Character '%c' not found\n", ch);
	}
	return (0);
} */
