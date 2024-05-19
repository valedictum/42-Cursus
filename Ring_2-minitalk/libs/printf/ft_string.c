/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:06:14 by atang             #+#    #+#             */
/*   Updated: 2023/08/21 10:28:38 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
ft_string iterates through each character of the input string, prints them 
using ft_character, and updates the char_count accordingly. It also handles 
the case when the input string is null, printing "(null)" and updating 
char_count by 6.

- char *s = pointer to string (character array) you want printed.
- int *char_count = pointer to an integer to keep track of the number of 
characters printed. 
- size_t for variable i as size_t is unsigned and specificailly designed to 
represent sizes and indices of objects so it is well-suited for string 
traversal.
 */

void	ft_string(char *s, int *char_count)
{
	size_t	i;

	if (!s)
	{
		write(1, "(null)", 6);
		(*char_count) += 6;
		return ;
	}
	i = 0;
	while (s[i] != '\0')
	{
		ft_character(s[i], char_count);
		i++;
	}
}
