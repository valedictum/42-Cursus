/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:11:59 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 09:47:19 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     memcpy -- copy memory area

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     void *
     memcpy(void *restrict dst, const void *restrict src, size_t n);

DESCRIPTION
     The memcpy() function copies n bytes from memory area src to memory area 
	 dst.  If dst and src overlap, behavior is undefined.  Applications in 
	 which dst and src might overlap should use memmove(3) instead.

RETURN VALUES
     The memcpy() function returns the original value of dst.
 */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}

/* int main()
{
    char src[] = "Hello World!";
    char dst[20];

	size_t n = ft_strlen(src) + 1;

    ft_memcpy(dst, src, n);
	printf("Copied string: %s\n", dst);
	return (0);
} */