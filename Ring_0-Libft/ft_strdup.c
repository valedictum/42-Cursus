/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:22:19 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 11:35:40 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
	strdup -- save a copy of a string

LIBRARY
    Standard C Library (libc, -lc)

SYNOPSIS
    #include <string.h>
	char *
    strdup(const char *s1);

DESCRIPTION
    The strdup() function allocates sufficient memory for a copy of the
    string s1, does the copy, and returns a pointer to it.  The pointer may
    subsequently be used as an argument to the function free(3).
	
	If insufficient memory is available, NULL is returned and errno is set to
    ENOMEM.
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* int	main(void)
{
	const char	*original = "Testing, testing!";
	char		*duplicate = ft_strdup(original);

	if (duplicate == NULL)
	{
		printf("Error: Failed to duplicate string");
		return (1);
	}
	printf("Original: %s\n", original);
	printf("Duplicate: %s\n", duplicate);
	free(duplicate);
	return (0);
} */
