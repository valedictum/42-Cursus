/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:25:42 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 17:24:33 by atang            ###   ########.fr       */
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
     The strchr() function locates the first occurrence of c (converted to a 
	 char) in the string pointed to by s.  The terminating null character is 
	 considered to be part of the string; there-fore if c is `\0', the 
	 functions locate the terminating `\0'.

     The strrchr() function is identical to strchr(), except it locates the 
	 last occurrence of c.

RETURN VALUES
     The functions strchr() and strrchr() return a pointer to the located 
	 character, or NULL if the character does not appear in the string.
*/
/*
	- set last pointer to the end, update the last pointer to current 
	position if a match found
	- check if the null terminator matches the target character and return 
	the address of the last occurrence (or NULL if not found)
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			last = s;
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return ((char *)last);
}

/* int	main(void)
{
	const char *str = "Hello, World!";
	char ch = 'l';
	char *ptr = ft_strrchr(str, ch);

	printf("String: %s\n", str);
	if (ptr != NULL)
	{
		printf("Last character '%c' found at: %ld\n", *ptr, ptr - str + 1);
	}
	else
	{
		printf("Character '%c' not found\n", ch);
	}
	return (0);
} */
