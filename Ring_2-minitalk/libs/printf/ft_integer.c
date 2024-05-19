/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:36:15 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:26:15 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
 ft_integer prints an integer number handling both negative and positive 
 numbers, recursively breaking down the number into its digits for printing.

 - when num is = to it, the most negative value (-2147483648) is printed and 
 char_count is updated by 11.
 - if num is negative (but not -2147483648), '-' is printed. Then, num is 
 converted to positive by negating it.
 - ft_integer is used recursively, breaking down the number into its individual 
 digits by continuously dividing it by 10 and printing each digit separately.
 - when num < 10, final digit is printed using ft_character (character 
 representation).
 - cast as char as ft_character expects char, not int.
 */

void	ft_integer(int num, int *char_count)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*char_count) += 11;
		return ;
	}
	if (num < 0)
	{
		ft_character('-', char_count);
		num = -num;
	}
	if (num >= 10)
	{
		ft_integer((num / 10), char_count);
	}
	ft_character((char)('0' + (num % 10)), char_count);
}
