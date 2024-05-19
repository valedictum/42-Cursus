/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:04:44 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:27:04 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
ft_pointer converts a pointer value into its hexadecimal representation and 
prints it with a '0x' prefix whilst also updating the char_count variable
to keep track of the number of characters printed throughout the function.

- pointer is of size_t type as size_t is an unsigned integer type, pointer size 
may vary, and size_t emphasises that the value represents memory address/size.
- 'string', an array of characters with size 25, is declared and is used for 
temporary storage of the hexadecimal representation of the pointer value in 
reverse order.
- *hexadecimal_base is a pointer to a character array to hold the 
hexadecimal digits, intialised to "0123456789abcdef" to enable mapping
between decimal values and their corresponding hexadecimal digits.
- '0' and 'x' are printed first as 0x is the standard hexadecimal prefix for 
memory addresses
- if value being pointed at is 0 (i.e. pointer =0), 0 is printed then return
- while NOT 0, the remainder of the modulus operation with 16 is given a value 
between 0 and 15 which is then indexed to access the corresponding hexadecimal
digit from hexadecimal_base. This digit is then store in the string array 
at 'i'. After using this remainder, pointer is divided by 16 (shifts to the 
right) before loop begins. This fills the 'string' array from reverse order. 
- the final while loop iterates through string in reverse order and prints 
using ft_character (first to last digit, reversing the reverse order) 
whilst also updating char_count.  
 */

void	ft_pointer(size_t pointer, int *char_count)
{
	char	string[25];
	int		i;
	char	*hexadecimal_base;

	hexadecimal_base = "0123456789abcdef";
	i = 0;
	ft_character('0', char_count);
	ft_character('x', char_count);
	if (pointer == 0)
	{
		ft_character('0', char_count);
		return ;
	}
	while (pointer != 0)
	{
		string[i] = hexadecimal_base [pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
		ft_character(string[i], char_count);
}
