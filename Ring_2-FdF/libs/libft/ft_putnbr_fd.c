/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:32:09 by atang             #+#    #+#             */
/*   Updated: 2023/07/30 10:51:43 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_putnbr_fd

Prototype
	void ft_putnbr_fd(int n, int fd);

Parameters
	n: The integer to output.
	fd: The file descriptor on which to write.

Return value
	None

External functs.
	write

Description
	Outputs the integer ’n’ to the given file descriptor.
 */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2147483648", 10);
			return ;
		}
		sign = -1;
		n = n * sign;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	digit = n % 10 + '0';
	write (fd, &digit, 1);
}

/* 
int	main(void)
{
	ft_putnbr_fd(-2147483648, 1);
	return (0);
}

 */