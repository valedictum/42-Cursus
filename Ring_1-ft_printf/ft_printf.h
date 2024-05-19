/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:11:56 by atang             #+#    #+#             */
/*   Updated: 2023/08/18 16:26:19 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

void	ft_character(char c, int *char_count);
void	ft_hexadecimal(unsigned int num, int uppercase, int *char_count);
void	ft_integer(int num, int *char_count);
void	ft_pointer(size_t pointer, int *char_count);
void	ft_string(char *s, int *char_count);
void	ft_unsigned_decimal(unsigned int num, int *char_count);
int		ft_printf(const char *string, ...);

#endif
