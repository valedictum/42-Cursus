/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:46:30 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 17:38:38 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     strlcpy, strlcat -- size-bounded string copying and concatenation

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     size_t
     strlcpy(char * restrict dst, const char * restrict src, size_t dstsize);

     size_t
     strlcat(char * restrict dst, const char * restrict src, size_t dstsize);

DESCRIPTION
     The strlcpy() and strlcat() functions copy and concatenate strings with 
	 the same input parameters and output result as snprintf(3).  They are 
	 designed to be safer, more consistent, and less error prone replacements 
	 for the easily misused functions strncpy(3) and strncat(3).

     strlcpy() and strlcat() take the full size of the destination buffer and 
	 guarantee NUL-termination if there is room.  Note that room for the NUL 
	 should be included in dstsize.

     strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
	 NUL-terminating the result if dstsize is not 0.

     strlcat() appends string src to the end of dst.  It will append at most 
	 dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless 
	 dstsize is 0 or the original dst string was longer than dstsize (in 
	 practice this should not happen as it means that either dstsize is 
	 incorrect or that dst is not a proper string).

     If the src and dst strings overlap, the behavior is undefined.

RETURN VALUES
     Besides quibbles over the return type (size_t versus int) and signal 
	 handler safety (snprintf(3) is not entirely safe on some systems), the 
	 following two are equivalent:

           n = strlcpy(dst, src, len);
           n = snprintf(dst, len, "%s", src);

     Like snprintf(3), the strlcpy() and strlcat() functions return the total 
	 length of the string they tried to create.  For strlcpy() that means the 
	 length of src.  For strlcat() that means the initial length of dst plus 
	 the length of src.

     If the return value is >= dstsize, the output string has been truncated. 
	 It is the caller's responsibility to handle this.
 */
/*
	- copy the characters from src to dst, respecting dstsize.
	- loop stops when it reaches the end of src or reaches (dstsize - 1) 
	(- 1 is to leave space for null terminator)
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len; 
	size_t	i;

	len = 0;
	i = 0;
	while (src[len] != '\0')
	{
		len++;
	}
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

/* int main() 
{
	const char* src = "Hello World!";
    char dst[15];

    size_t len = ft_strlcpy(dst, src, sizeof(dst));

    printf("Copied string: %s\n", dst);
    printf("Length of the source string: %zu\n", len);
    return (0);
} */