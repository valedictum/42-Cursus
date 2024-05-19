/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:09:10 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 10:49:26 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     memset -- fill a byte string with a byte value

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     void *
     memset(void *b, int c, size_t len);

DESCRIPTION
     The memset() function writes len bytes of value c (converted to an 
	 unsigned char) to the string b.

RETURN VALUES
     The memset() function returns its first argument.
 */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char) c;
		i++;
	}
	return (b);
}

/* int main(void)
{
    char str[21];

    ft_memset(str, 'A', sizeof(str) - 1);
    str[sizeof(str) - 1] = '\0';
	printf("Filled string: %s\n", str);
    return 0;
} */
