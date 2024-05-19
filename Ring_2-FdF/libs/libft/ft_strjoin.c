/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:14:23 by atang             #+#    #+#             */
/*   Updated: 2024/01/19 18:55:55 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_strjoin

Prototype
	char *ft_strjoin(char const *s1, char const *s2);

Parameters
	s1: The prefix string.
	s2: The suffix string.

Return value
	The new string.
	NULL if the allocation fails.

External functs.
	malloc

Description
	Allocates (with malloc(3)) and returns a new string, which is 
	the result of the concatenation of ’s1’ and ’s2’.
*/
/*
	- if memory allocation is successful, content of s1 is copied 
	into the result, then the content of s2 is copied into the result 
	starting from the position immediately after the end of s1.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	total_len;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total_len = len_s1 + len_s2;
	result = (char *)malloc((total_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, len_s1);
	ft_memcpy(result + len_s1, s2, len_s2);
	result[total_len] = '\0';
	return (result);
}

/* int	main(void)
{
	char	*s1 = "Hey! ";
	char	*s2 = "How are you?";
	char	*result; 

	result = ft_strjoin(s1, s2);
	printf("String 1: %s\n", s1);
	printf("String 2: %s\n", s2);
	if (result != NULL)
	{
		printf("%s\n", result);
		free(result);
	}
	else
		printf("Memory allocation error or invalid input strings.\n");
	return (0);
} */
