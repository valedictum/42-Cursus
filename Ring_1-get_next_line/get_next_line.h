/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:49:29 by atang             #+#    #+#             */
/*   Updated: 2023/09/08 10:34:33 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	gnl_strlen(const char *str);
char	*gnl_strchr(char *str, int target_char);
char	*gnl_strjoin(char *first_str, char *second_str);
char	*gnl_initialise_str(void);
char	*read_and_append_lines(int fd, char	*stash);
char	*extract_line_from_stash(char	*stash);
char	*remaining_stash_after_extraction(char *stash);
char	*get_next_line(int fd);

#endif
