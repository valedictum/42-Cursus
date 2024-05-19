/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:15:56 by atang             #+#    #+#             */
/*   Updated: 2024/01/28 11:10:30 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
calculate_colour() takes two integers, z and z1, and returns an integer value 
representing the colour based on the values of z and z1. If either z or z1 are 
less than 0, red is returned. If z and z1 = 0, white is returned. If both z 
and z1 are greater than or equal to zero, green is returned. If none of the 
conditions are met, final colour is calculated by interpolating between + and -
colour based on ratio of z to (z + z1). 
*/

static int	calculate_colour(int z, int z1)
{
	int	neg_colour;
	int	zero_colour;
	int	pos_colour;
	int	final_colour;

	neg_colour = 0xFF0000;
	zero_colour = 0xFFFFFF;
	pos_colour = 0x00FF00;
	if (z < 0 || z1 < 0)
		return (neg_colour);
	else if (z == 0 && z1 == 0)
		return (zero_colour);
	else if (z >= 0 && z1 >= 0)
		return (pos_colour);
	else
	{
		final_colour = pos_colour + ((neg_colour - pos_colour) * z) / (z + z1);
		return (final_colour);
	}
}

/*
plot_pixel() plots a pixel on a graphic window. fn initialises the width to 
1920, checks if x and y co-ordinates are within the bounds of the window and, 
if so, calculates the index of the pixel in the img_data array (row number x 
width of image then add column number). Then, the colour of the pixel is set 
to the colour stored in  the colour variable of the 'data' structure. 
*/

void	plot_pixel(int x, int y, t_fdf *data)
{
	int	width;
	int	img_index;

	width = 1920;
	if (x >= 0 && x < width && y >= 0 && y < 1080)
	{
		img_index = (int)y * width + (int)x;
		data->img_data[img_index] = data->colour;
	}
}

/*
bresenham() implements the Bresenham's line algorithm to draw a line 
on a graphics window. It takes the start and end co-ordinates of the 
line as well as a structure pointer 'data' that contains information 
such as zoom level, colour, shift value etc.

Inputs are a start structure (representing the start of the line, 
containing the x, y, z co-ordinates), an end structure (same but for the 
end point of the line), and a pointer to the structure that contains 
additional line-drawing information.

The function:
- initialises x, y, x1, y1 with the scaled and shifted co-ordinates of 
the start and end points
- caculates the colour of the line based on the z values of the start 
and end points
- applies isometric transformation to the co-ordinates using isometric()
- calculates the max value between the absolute differences of x1 -x and 
y1 - y
- until the difference between x and x1 or y and y1 is not zero, plots a
pixel at the current co-ordinates using plot_pixel(), incrementing x and y
by the step sizes respectively. 
*/

void	bresenham(t_point start, t_point end, t_fdf *data)
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	max_value;

	x = (int)start.x * data->zoom;
	y = (int)start.y * data->zoom;
	x1 = (int)end.x * data->zoom;
	y1 = (int)end.y * data->zoom;
	data->colour = calculate_colour((int)start.z, (int)end.z);
	isometric(&x, &y, (int)start.z * data->amplify);
	isometric(&x1, &y1, (int)end.z * data->amplify);
	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;
	max_value = max(mod(x1 - x), mod(y1 - y));
	while ((int)(x - x1) || (int)(y - y1))
	{
		plot_pixel(x, y, data);
		x += (x1 - x) / max_value;
		y += (y1 - y) / max_value;
	}
}

/*
draw() iterates over height and width of the 'data' structure and 
calls bresenham() to draw lines between each dot on the grid, taking 
a pointer to the t_fdf 'data' structure as input.

Draws lines between every dot as below:

	0->		0->		0->		0
	|		|		|		|
	
	0->		10->	10->	0
	|		|		|		|

	0->		10->	10->    0
	|		|		|		|

	0->		0->		0->		0
'->' and '|'are lines between dots

Every dot has two lines (right and down):	0->
											|
(Boundary dots are exceptions)

- inside the nested loop which iterates over height and width, it
checks if x is less than width - 1 (if so, bresenham() is called to 
draw a line from the current dot to the dot on its right). then y is
checked to see if it is less than height - 1 (if so, bresenham() is 
called to draw a line from the current dot to the dot below it)
- x++, then when out of the inner loop, y++ until y reaches the height 
of the grid 

N.B By -1 from height and width, we are only drawing lines within the
valid range of the grid i.e (width - 1) to ensure it is not the last dot
in the row (draws L to R), and (height - 1) to ensure it is not the last
dot in the column (draws T to B)
*/

void	draw(t_fdf *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresenham((t_point){x, y, data->z_matrix[y][x]},
					(t_point){x + 1, y, data->z_matrix[y][x + 1]}, data);
			if (y < data->height - 1)
				bresenham((t_point){x, y, data->z_matrix[y][x]},
					(t_point){x, y + 1, data->z_matrix[y + 1][x]}, data);
			x++;
		}
		y++;
	}
}
