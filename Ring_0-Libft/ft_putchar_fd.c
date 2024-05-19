/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:45:45 by atang             #+#    #+#             */
/*   Updated: 2023/07/20 16:13:07 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_putchar_fd

Prototype
	void ft_putchar_fd(char c, int fd);

Parameters
	c: The character to output.
	fd: The file descriptor on which to write.

Return value
	None

External functs.
	write
	
Description
	Outputs the character ’c’ to the given file descriptor.
 */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int main(void)
{
	char	c = 'A';
    int		fd = 1;

    ft_putchar_fd(c, fd);
	ft_putchar_fd('\n', fd);
    return (0);
} */
