/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:58:30 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 16:55:21 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     tolower -- upper case to lower case letter conversion

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <ctype.h>

     int
     tolower(int c);

DESCRIPTION
     The tolower() function converts an upper-case letter to the corresponding 
	 lower-case letter. The argument must be representable as an unsigned char 
	 or the value of EOF.

RETURN VALUES
     If the argument is an upper-case letter, the tolower() function returns the 
	 corresponding lower-case letter if there is one; otherwise, the argument is 
	 returned unchanged.
 */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/* int main()
{
    int c = 'Q';
	int result = ft_tolower(c);
    printf("Character is: %c\n", c);    
    printf("Lowercase equivalent: %c\n", result);
    return (0);
} */
