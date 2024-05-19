/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:02:48 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:26:13 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
ft_hexadecimal takes the number you want to convert to hexadecimal (num), 
a case flag where upper is 1 and lower is 0 (uppercase), and the running 
char_count tracker.

- hex_digits array is initialised with the appropriate set of hexadecimal 
digits based on whether uppercase flag is set to 1 (uppercase) or 0 
(lowercase).
- then, the function proceeds with recursive breakdown of the unsigned integer 
into its hexadecimal representation. If n >= 16, n / 16 and then it prints the 
corresponding hexadecimal digit using ft_character. Lastly, ft_character and 
n % 16 are used to calculate and print the remainder.
- else block handles the case where n < 16 meaning there is a single 
hexadecimal which is printed directly using ft_character.
*/

void	ft_hexadecimal(unsigned int num, int uppercase, int *char_count)
{
	char	*hex_digits;

	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (num >= 16)
	{
		ft_hexadecimal(num / 16, uppercase, char_count);
		ft_character(hex_digits[num % 16], char_count);
	}
	else
		ft_character(hex_digits[num], char_count);
}
