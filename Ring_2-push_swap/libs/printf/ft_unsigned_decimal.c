/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_decimal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:37:21 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:26:22 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
ft_unsigned_decimal recursively breaks down the number into its digits, 
prints them using ft_character, and handles positive unsigned integers.

- ft_unsigned_decimal recursively divides the unsigned integer number by 10 
and prints each digit separately.
 - when num < 10, final digit is printed using ft_character (character 
 representation).
 */

void	ft_unsigned_decimal(unsigned int num, int *char_count)
{
	if (num >= 10)
		ft_unsigned_decimal((num / 10), char_count);
	ft_character('0' + (num % 10), char_count);
}
