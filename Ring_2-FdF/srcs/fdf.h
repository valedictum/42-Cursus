/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:55:45 by atang             #+#    #+#             */
/*   Updated: 2024/01/21 15:01:02 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/libft/libft.h"
# include "../minilibx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_point
{
	float	x;
	float	y;
	int		z;
}			t_point;

typedef struct s_step
{
	float	x_step;
	float	y_step;
	float	x;
	float	y;
	float	x1;
	float	y1;
}			t_step;

typedef struct s_fdf
{
	int				width;
	int				height;
	int				**z_matrix;
	int				zoom;
	int				colour;
	int				amplify;
	int				shift_x;
	int				shift_y;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	t_point			start;
	t_point			end;
}			t_fdf;

//--- draw_utils.c ---//
int		max(int a, int b);
float	mod(float a);
void	isometric(float	*x, float *y, int z);
//--- draw.c ---//
void	plot_pixel(int x, int y, t_fdf *data);
void	bresenham(t_point start, t_point end, t_fdf *data);
void	draw(t_fdf *data);
//--- error.c ---//
int		file_exists(char *file_name);
int		file_name_error(char	*file_name);
void	handle_exit(t_fdf *data);
int		close_button_hook(t_fdf *data);
//--- fdf.c ---//
int		deal_key(int key, t_fdf *data);
void	initialise_data(t_fdf *data, char *filename);
void	render_and_loop(t_fdf *data);
//--- get_next_line_utils.c ---//
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(char *str, int target_char);
char	*gnl_strjoin(char *first_str, char *second_str);
char	*gnl_initialise_str(void);
//--- get_next_line.c ---//
char	*read_and_append_lines(int fd, char	*stash);
char	*extract_line_from_stash(char	*stash);
char	*remaining_stash_after_extraction(char *stash);
char	*get_next_line(int fd, char **line);
//--- read_file.c ---//
int		get_height(char	*file_name);
int		get_width(char	*file_name);
void	fill_matrix(int **data, char *line);
void	read_file(char	*file_name, t_fdf	*data);

#endif
