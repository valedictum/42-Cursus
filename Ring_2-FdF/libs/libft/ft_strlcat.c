/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:18:13 by atang             #+#    #+#             */
/*   Updated: 2024/01/19 18:58:24 by atang            ###   ########.fr       */
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
     The strlcpy() and strlcat() functions copy and concatenate strings with the 
	 same input parameters and output result as snprintf(3).  They are designed 
	 to be safer, more consistent, and less error prone replacements for the 
	 easily misused functions strncpy(3) and strncat(3).

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

     Like snprintf(3), the strlcpy() and strlcat() functions return the 
	 total length of the string they tried to create.  For strlcpy() that means 
	 the length of src.  For strlcat() that means the initial length of dst 
	 plus the length of src.

     If the return value is >= dstsize, the output string has been truncated. 
	 It is the caller's responsibility to handle this.
 */
/*
	- dstsize is max size allowed for dst
	- if the dst buffer is already full (dst_len == dstsize), return the 
	total length if we were to append src to dst (dstsize + src_len) to ensure 
	that the dst buffer remains null-terminated
	- return the total length of the concatenated string (dst_len + src_len) 
	excluding the null-terminator
*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	src_len = 0;
	i = 0;
	while (dst[dst_len] != '\0' && dst_len < dstsize)
		dst_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (dst_len == dstsize)
		return (dstsize + src_len);
	while (i < (dstsize - dst_len - 1) && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* int main(void)
{
    char destination[20] = "Hello, ";
    const char *source = "world!";
    size_t dstsize = sizeof(destination);
    
    printf("Before concatenation:\n");
    printf("Destination: %s\n", destination);
    printf("Source: %s\n", source);
    
    size_t result = ft_strlcat(destination, source, dstsize);
    
    printf("\nAfter concatenation:\n");
    printf("Destination: %s\n", destination);
    printf("Resultant length: %zu\n", result);
    
    return 0;
} */
