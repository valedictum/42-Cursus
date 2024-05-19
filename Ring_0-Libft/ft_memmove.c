/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:11:25 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 16:52:25 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     memmove -- copy byte string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     void *
     memmove(void *dst, const void *src, size_t len);

DESCRIPTION
     The memmove() function copies len bytes from string src to string dst.  
	 The two strings may overlap; the copy is always done in a non-destructive 
	 manner.

RETURN VALUES
     The memmove() function returns the original value of dst.
 */
/* 
	- if dst_ptr == src_ptr, the pointers are pointing to the same memory 
	location, meaning that the source and destination memory regions overlap, 
	and there is no need to perform any copy operation so the function 
	directly returns the dst pointer.
	- if src_ptr < dst_ptr, copy from back (backwards)
	- if src_ptr > dst_ptr, copy from front (forward)
 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_ptr;
	const char	*src_ptr;

	dst_ptr = (char *)dst;
	src_ptr = (const char *)src;
	if (dst_ptr == src_ptr)
		return (dst);
	if (src_ptr < dst_ptr)
		while (len --)
			dst_ptr[len] = src_ptr[len];
	else
		while (len--)
			*dst_ptr++ = *src_ptr++;
	return (dst);
}

/* int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    // Move the last three elements two positions to the right
    ft_memmove(arr + 2, arr + 1, 3 * sizeof(int));

    // Output: 1 2 2 3 4
    for (int i = 0; i < 5; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
} */

/* int main() {
    // Test case 1: Move elements within an array
    int arr1[5] = {1, 2, 3, 4, 5};
    ft_memmove(arr1 + 2, arr1 + 1, 3 * sizeof(int));
    // Expected output: 1 2 2 3 4
    printf("Test case 1: ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // Test case 2: Move elements between non-overlapping arrays
    int src2[4] = {10, 11, 12, 13};
    int dest2[4] = {0};
    ft_memmove(dest2, src2, 4 * sizeof(int));
    // Expected output: 10 11 12 13
    printf("Test case 2: ");
    for (int i = 0; i < 4; ++i) {
        printf("%d ", dest2[i]);
    }
    printf("\n");

    // Test case 3: Move elements between overlapping arrays
    int arr3[6] = {1, 2, 3, 4, 5, 6};
    ft_memmove(arr3 + 1, arr3 + 3, 3 * sizeof(int));
    // Expected output: 1 4 5 6 5 6
    printf("Test case 3: ");
    for (int i = 0; i < 6; ++i) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    // Test case 4: Move characters within a string
    char str4[10] = "HelloWorld";
    ft_memmove(str4 + 3, str4 + 7, 5 * sizeof(char));
    // Expected output: Helrld
	printf("Test case 4: %s\n", str4);
    
	return (0);
} */