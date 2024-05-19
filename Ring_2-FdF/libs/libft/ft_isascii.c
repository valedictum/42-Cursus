/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:30:54 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 16:47:11 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     isascii -- test for ASCII character

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <ctype.h>

     int
     isascii(int c);

DESCRIPTION
     The isascii() function tests for an ASCII character, which is any 
	 character between 0 and octal 0177 inclusive.
 */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* int main()
{
    int ch = '&';
    
    printf("The character is: %c\n", ch);
    if (ft_isascii(ch))
        printf("%d is an ASCII character.\n", ch);
    else
        printf("%d is not an ASCII character.\n", ch);
    return (0);
} */
