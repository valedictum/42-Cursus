/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:50:45 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 17:55:47 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_strmapi

Prototype
	char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

Parameters
	s: The string on which to iterate.
	f: The function to apply to each character.

Return value
	The string created from the successive applications of ’f’.
	Returns NULL if the allocation fails.

External functs.
	malloc

Description
	Applies the function ’f’ to each character of the string ’s’, and passing 
	its index as first argument to create a new string (with malloc(3)) 
	resulting from successive applications of ’f’.
 */
/*
 	- second while loop iterates through s string and applies the function 
	f to each character. The result of f(i, s[i]) is stored in the 
	corresponding index of the result string. The function f is called 
	with the current index i and the character at that index s[i].
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*result;

	len = 0;
	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[len] != '\0')
	{
		len++;
	}
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}
/* 
static char	function_pointer(unsigned int index, char c)
{
	(void) index;
	return (c + 1);
}

int	main(void)
{
	const char	*test_str = "Hello, World!";
	char		*result_str = ft_strmapi(test_str, function_pointer);

	if (result_str != NULL)
	{
		printf("Original string: %s\n", test_str);
		printf("Modified string: %s\n", result_str);
		free(result_str);
	}
	else 
	{
		printf("Memory allocation failed.\n");
	}
	return (0);
}
 */