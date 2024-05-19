/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_character.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:05:40 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:26:12 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
ft_character prints a single character to the standard output and updates the 
char_count to keep track of the number of characters printed.

- (*char_count) dereferences the pointer char_count to get the value it 
points to (an integer).
- char_count is passed as a pointer so that any changes made to it within this
 function will also affect the original variable in the calling function so 
 the total number of characters printed is accumulated and maintained across 
 different function calls
 */

void	ft_character(char c, int *char_count)
{
	write(1, &c, 1);
	(*char_count)++;
}
