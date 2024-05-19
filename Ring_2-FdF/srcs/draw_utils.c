/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:36:22 by atang             #+#    #+#             */
/*   Updated: 2024/01/28 11:07:34 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
Helper function to calculate the maximum between 2 values (i.e. the larger 
value)
*/

int	max(int a, int b)
	{
	if (a > b)
		return (a);
	else
		return (b);
}

/*
Helper function to calculate the modulus to find the absolute value
*/

float	mod(float a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

/*
isometric() Performs calculations to transform the x and y co-ordinates 
based on an isometric projection, updating x and y accordingly. It takes 
2 float pointers (x, y) and an integer (z) as parameters.
*/

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}
