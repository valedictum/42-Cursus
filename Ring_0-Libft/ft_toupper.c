/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:24 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 16:55:36 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     toupper -- lower case to upper case letter conversion

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <ctype.h>

     int
     toupper(int c);

DESCRIPTION
     The toupper() function converts a lower-case letter to the corresponding 
	 upper-case letter.  The argument must be representable as an unsigned char 
	 or the value of EOF.

RETURN VALUES
     If the argument is a lower-case letter, the toupper() function returns 
	 the corresponding upper-case letter if there is one; otherwise, the argument 
	 is returned unchanged.
 */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/* int main()
{
    int c = 'b';
	int result = ft_toupper(c);
    printf("Character is: %c\n", c);    
    printf("Uppercase equivalent: %c\n", result);
    return (0);
} */