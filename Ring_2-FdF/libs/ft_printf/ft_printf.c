/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:40:48 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:26:17 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
static helper function ft_format_type takes a char, fs (format specifier), and 
a pointer, args_ptr, to a variable list of arguments (variable by number and 
type).

- char_count keeps track of characters printed within this function call.
- functions are called based on fs where va_arg(*args_ptr, TYPE) retrieves the 
next argument from the list and interprets it as TYPE e.g int) before passing 
it to the relevent function and char count is passed so that the characters 
printed can be updated.
- ft_pointer takes a size_t argument so void* is cast to size_t before passing 
to ft_pointer.
- if fs is not any of the recognised format specifiers 
('c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'), then fs represents 
regular text to print as is. ft_character is called with fs (the character 
itself) printed as is and char_count updated.
 */

static int	ft_format_type(char fs, va_list *args_ptr)
{
	int	char_count;

	char_count = 0;
	if (fs == 'c')
		ft_character(va_arg(*args_ptr, int), &char_count);
	else if (fs == 's')
		ft_string(va_arg(*args_ptr, char *), &char_count);
	else if (fs == 'p')
		ft_pointer((size_t)va_arg(*args_ptr, void *), &char_count);
	else if (fs == 'd' || fs == 'i')
		ft_integer(va_arg(*args_ptr, int), &char_count);
	else if (fs == 'u')
		ft_unsigned_decimal(va_arg(*args_ptr, unsigned int), &char_count);
	else if (fs == 'x')
		ft_hexadecimal(va_arg(*args_ptr, unsigned int), 0, &char_count);
	else if (fs == 'X')
		ft_hexadecimal(va_arg(*args_ptr, unsigned int), 1, &char_count);
	else if (fs == '%')
		ft_character('%', &char_count);
	else
		ft_character(fs, &char_count);
	return (char_count);
}

/* 
ft_printf is the main function that emulates the behaviour of the standard 
printf. It uses a variable argument list (va_list) to process the variable 
number of arguments. It takes a string 'string' as its first argument, which 
contains the text to be printed. The '...' indicates that there can be a 
variable number of additional arguments.

- initialises va_list (args_ptr which manages the variable arguments 
by storing the argument list) using va_start (which finds the starting address 
of the variable arguments based on the provided string). 
- initialises printed_chars to keep track of the total number of characters 
printed.
- iterates through each character in the string using loop counter, i.
- if the current character is %, it indicates a format specifier, with the 
character after % is used to determine the type of format. The ft_format_type 
function is called with the character at string[i] as the format 
specifier, and args_ptr as the argument list. ft_format_type returns the 
number of printed characters which is then added to the printed_chars count. 
This keeps track of the total number of characters that have been printed 
so far.
- if the current character is not %, it means regular text that needs to be 
printed as is with casting to char to make sure the correct data type is 
passed to the function. The address of printed_chars is passed so that the 
character count can be updated.
- function processes each format specifier or regular character by calling 
the appropriate function and updating the printed_chars count.
- ends by cleaning up the va_list using va_end and returns the total number 
of characters printed.
 */

int	ft_printf(const char *string, ...)
{
	va_list	args_ptr;
	int		printed_chars;
	int		i;

	va_start(args_ptr, string);
	printed_chars = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			printed_chars += ft_format_type(string[i], &args_ptr);
			i++;
		}
		else
		{
			ft_character((char)string[i], &printed_chars);
			i++;
		}
	}
	va_end(args_ptr);
	return (printed_chars);
}

/* 
Program name 
	libftprintf.a
Turn in files 
	Makefile, *.h, star/star.h, *.c, star/star.c
Makefile 
	NAME, all, clean, fclean, re
External functs.
	malloc, free, write, va_start, va_arg, va_copy, va_end
Libft authorized
	Yes
Description
	Write a library that contains ft_printf(), a function that will mimic the 
	original printf().
	
You have to recode the printf() function from libc. The prototype of ft_printf()
is:
int ft_printf(const char *, ...);

Here are the requirements:
• Don’t implement the buffer management of the original printf().
• Your function has to handle the following conversions: cspdiuxX%
• Your function will be compared against the original printf().
• You must use the command ar to create your library.
Using the libtool command is forbidden.
• Your libftprintf.a has to be created at the root of your repository.
You have to implement the following conversions:
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format. 
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
 */
