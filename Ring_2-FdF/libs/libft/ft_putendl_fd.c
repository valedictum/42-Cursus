/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:15:05 by atang             #+#    #+#             */
/*   Updated: 2023/07/21 10:38:46 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_putendl_fd

Prototype
	void ft_putendl_fd(char *s, int fd);

Parameters
	s: The string to output.
	fd: The file descriptor on which to write.

Return value
	None

External functs.
	write

Description
	Outputs the string ’s’ to the given file descriptor followed by a newline.
 */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/* int main(void)
{
    char *s = "Hello World!";
    int fd = 1;

    ft_putendl_fd(s, fd);
	return (0);
} */