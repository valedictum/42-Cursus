/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:20:51 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 16:37:16 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
NAME
     isdigit, isnumber -- decimal-digit character test

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <ctype.h>

     int
     isdigit(int c);

     int
     isnumber(int c);

DESCRIPTION
     The isdigit() function tests for a decimal digit character.  Regardless 
	 of locale, this includes the following characters only:

     ``0''         ``1''         ``2''         ``3''         ``4''
     ``5''         ``6''         ``7''         ``8''         ``9''

     The isnumber() function behaves similarly to isdigit(), but may recognize
	 additional characters, depending on the current locale setting.

     The value of the argument must be representable as an unsigned char or 
	 the value of EOF.

RETURN VALUES
     The isdigit() and isnumber() functions return zero if the character 
	 tests false and return non-zero if the character tests true.
 */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* int main()
{
    int c = 'A';

    printf("The character is: %c\n", c);
    if (ft_isdigit(c))
        printf("%c is a digit.\n", c);
    else
        printf("%c is not a digit.\n", c);
    return (0);
} */