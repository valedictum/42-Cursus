/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:49:51 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 16:10:50 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_striteri

Prototype
	void ft_striteri(char *s, void (*f)(unsigned int, char*));

Parameters
	s: The string on which to iterate.
	f: The function to apply to each character.

Return value
	None.

External functs.
	None.

Description
	Applies the function ’f’ on each character of the string passed as 
	argument, passing its index as first argument. Each character is passed 
	by address to ’f’ to be modified if necessary.

 */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		f(i, s);
		s++;
		i++;
	}
}

/* static	void	modify_and_print(unsigned int index, char *character)
{
	if (*character >= 'a' && *character <= 'z')
		*character -= 32;
	printf("Index %u: %c\n", index, *character);
}

int	main(void)
{
	char	test_string[] = "Hello, world!";

	printf("Original string: %s\n", test_string);
	ft_striteri(test_string, modify_and_print);
	return (0);
} */
