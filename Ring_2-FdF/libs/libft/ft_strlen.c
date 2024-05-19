/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:50:30 by atang             #+#    #+#             */
/*   Updated: 2023/07/21 12:31:47 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     strlen -- find length of string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     size_t
     strlen(const char *s);

DESCRIPTION
     The strlen() function computes the length of the string s.  The strnlen()
	 function attempts to compute the length of s, but never scans beyond the 
	 first maxlen bytes of s.

RETURN VALUES
     The strlen() function returns the number of characters that precede the 
	 terminating NUL character.  The strnlen() function returns either the same 
	 result as strlen() or maxlen, whichever is smaller.
 */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/* int	main(void)
{
	const char	*str;

	str = "Hello there!";
	printf("%s\n", str);
	printf("Number of characters: %d\n", ft_strlen(str));
	return (0);
} */
