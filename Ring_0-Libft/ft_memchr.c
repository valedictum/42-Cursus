/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:24:34 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 17:07:01 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
     memchr -- locate byte in byte string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     void *
     memchr(const void *s, int c, size_t n);

DESCRIPTION
     The memchr() function locates the first occurrence of c (converted to 
	 an unsigned char) in string s.

RETURN VALUES
     The memchr() function returns a pointer to the byte located, or NULL if 
	 no such byte exists within n bytes.
*/
/* 
	- constant unsigned char pointer is used to access the memory location 
	it points to, so you can read the value stored there (since it's a 
	read-only pointer), but you cannot modify the value using this pointer
	- (p = s) points the pointer 'p' to the start of the memory block 
	pointed by 's'.
	- if a match is found (p[i] == target), return a pointer to the 
	location of the match in memory (the (void *) typecast is used to 
	convert the pointer to void* type because the function return type 
	is void*.)
 */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		target;
	size_t				i;

	p = s;
	i = 0;
	target = (unsigned char)c;
	while (i < n)
	{
		if (p[i] == target)
		{
			return ((void *)(p + i));
		}
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char	buffer[] = "Congratulations!";
	char	ch = 't';
	char	*result = ft_memchr(buffer, ch, ft_strlen(buffer));

	printf("String: %s\n", buffer);
	if (result != NULL)
		printf("Found '%c' at position %ld\n", ch, result - buffer);
	else
		printf("Character not found.\n");
	return (0);
} */
