/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 21:52:59 by atang             #+#    #+#             */
/*   Updated: 2023/07/24 16:19:59 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_itoa

Prototype
	char *ft_itoa(int n);

Parameters
	n: the integer to convert.

Return value
	The string representing the integer. 
	NULL if the allocation fails.

External functs.
	malloc

Description
	Allocates (with malloc(3)) and returns a string representing the integer 
	received as an argument. Negative numbers must be handled.
*/

/* 
	negsign = 1 if negative, 0 if positive, (num /=10) is (num = num / 10)
 */

#include "libft.h"

static int	count_digits(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

char	*ft_itoa(int num)
{
	int		negsign; 
	int		len;
	char	*str;

	negsign = (num < 0);
	len = count_digits(num);
	str = (char *)malloc((len + negsign + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len + negsign] = '\0';
	while (len-- > 0)
	{
		if (negsign)
			str[len + negsign] = -(num % 10) + '0';
		else
			str[len + negsign] = (num % 10) + '0';
		num /= 10;
	}
	if (negsign)
		str[0] = '-';
	return (str);
}

/* 
int	main(void)
{
	int		num = -23487967;
	char	*result = ft_itoa(num);

	if (result != NULL)
	{
		printf("ft_itoa(%d) = %s\n", num, result);
		free(result);
	}
	return (0);
}
 */
