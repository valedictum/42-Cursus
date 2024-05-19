/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:15:24 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 18:00:03 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_substr

Prototype
	char *ft_substr(char const *s, unsigned int start, size_t len);

Parameters
	s: The string from which to create the substring. 
	start: The start index of the substring in the string ’s’.
	len: The maximum length of the substring.

Return value 
	The substring.
	NULL if the allocation fails.

External functs.
	malloc
 
Description
	Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of maximum size ’len’.
*/
/*
	- first if is if the starting index 'start' is greater than or equal 
	to the length of 's' or the length 'len' is 0, return an empty string.
	- remaining length after the starting index (start)
	- if len > remaining length, len set to the remaining length
	to avoid going beyond the end of the original string
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	remaining_len;
	char	*substring;

	s_len = ft_strlen(s);
	if (start >= s_len || len == 0)
	{
		return (ft_strdup(""));
	}
	remaining_len = s_len - start;
	if (len > remaining_len)
	{
		len = remaining_len;
	}
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (substring == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(substring, s + start, len + 1);
	substring[len] = '\0';
	return (substring);
}
/* 
int	main(void)
{
	char	*substring;
	char	input_string[] = "Hello, world!";
	unsigned int	start_index = 7;
	size_t	substring_length = 5;


	printf("String: %s\n", input_string);
	substring = ft_substr(input_string, start_index, substring_length);
	if (substring != NULL)
	{
		printf("Substring: %s\n", substring);
		free(substring);
	}
	else
	{
		printf("Substring allocation failed.\n");
	}
	return (0);
}
 */