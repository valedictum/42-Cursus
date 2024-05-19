/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:06:55 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 10:46:05 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     bzero -- write zeroes to a byte string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <strings.h>

     void
     bzero(void *s, size_t n);

DESCRIPTION
     The bzero() function writes n zeroed bytes to the string s.  If n is 
	 zero, bzero() does nothing.

 */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/* int main() 
{
    char buffer[10] = "Hello";
    
    printf("Original: %s\n", buffer);
    ft_bzero(buffer, sizeof(buffer));
    printf("After ft_bzero: %s\n", buffer);
    return (0);
} */