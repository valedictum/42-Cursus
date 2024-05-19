/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:56:00 by atang             #+#    #+#             */
/*   Updated: 2024/01/28 11:15:05 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
deal_key() handles keyboard input events and takes the following 
parameters as input: 
- an integer (key - a key code to represent the pressed key) 
- a pointer (data) to an fdf structure that contains program data

Key codes:
- Pan (display moved up/down/left/right):
126 = up, 125 = down, 123 = left, 124 = right
- Zoom (in/out):
69 = + (plus), 78 = - (minus)
- Amplify (+/-):
67 = increase amplification, 75 = reduce amplification 
- Exit (destroy window, free memory, and exit the program)
53 = Esc (escape)

b_zero() is used to clear the data->img_data buffer, while 
mlx_clear_window() is used to clear the window itself.
*/

int	deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	if (key == 126)
		data->shift_y -= 50;
	else if (key == 125)
		data->shift_y += 50;
	else if (key == 123)
		data->shift_x -= 50;
	else if (key == 124)
		data->shift_x += 50;
	else if (key == 69)
		data->zoom += 1;
	else if (key == 78)
		data->zoom -= 1;
	else if (key == 67)
		data->amplify += 1;
	else if (key == 75)
		data->amplify -= 1;
	else if (key == 53)
		handle_exit(data);
	ft_bzero(data->img_data, 1920 * 1080 * (data->bpp / 8));
	draw(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

/*
Helper function to initialise the data structure with values:
- amplify set to 1
- reads the file specified by argv[1] and stores the data in the 'data'
structure
- initialises the mlx library and assigns the returned pointer to data->mlx_ptr
(mlx_init() establishes connection to the X-Window server (i.e. creates a 
structure and returns the address of a struct (Xvar) that has all the things 
minilibx needs to work including display which is another large struct)
- creates a new window of 1920x1080 pixels titled FDF using mlx_new_window
and assigns the returned pointer to data->win_ptr (malloc-ed new window)
- mlx_new_image() is used to create a new image with dimnesions of 1920 x 1080 
and the return pointer is assigned to data->img_ptr
- mlx_get_data_addr() is called to get the address of the image data and assign 
it to data->img_data
- zoom and shift are initialised  
*/

void	initialise_data(t_fdf *data, char *filename)
{
	data->amplify = 1;
	read_file(filename, data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "FDF");
	data->img_ptr = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->img_data = (unsigned int *)mlx_get_data_addr(data->img_ptr,
			&data->bpp, &data->size_line, &data->endian);
	data->zoom = 20;
	data->shift_x = (1920 - data->width * data->zoom) / 2;
	data->shift_y = (1080 - data->height * data->zoom) / 2;
}

/*
Helper function that renders the image and starts the event loop for keyboard
input. draw() is used to render the image and then put into the window using
mlx_put_image_to_window(). deal_key() is registered as the keyboard event 
handler using mlx_key_hook() (Hooks 'hook' into an event (i.e. they react to
events). In this case, when a key is pressed (the event), deal_key() is called.
The event loop is started with mlx_loop() which essentially is an infinite loop
which keeps the process alive waiting for events (which were registered before 
the loop started) to be triggered.
*/
void	render_and_loop(t_fdf *data)
{
	draw(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_ptr, 0, 0);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_hook(data->win_ptr, 17, 0, close_button_hook, data);
	mlx_loop(data->mlx_ptr);
}

/*
main():
- checks for correct # and format of parameters
- if the file exists, fn allocates memory for the data structureand initialises 
it with file data
- the mlx library is initialised and creates a new window, sets the zoom
level, and calls draw() to display the initial image
- fn registers deal_key() as the keyboard event handler and starts the event 
loop using mlx_loop  
*/

int	main(int argc, char **argv)
{
	t_fdf	*data;
	int		i;

	data = NULL;
	i = 0;
	if (argc != 2 || file_name_error(argv[1]))
		ft_printf("Error!\nUsage: ./fdf <filename>.fdf\n");
	else if (file_exists(argv[1]))
	{
		data = (t_fdf *)malloc(sizeof(t_fdf));
		if (data == NULL)
			return (1);
		initialise_data(data, argv[1]);
		render_and_loop(data);
	}
	else
		ft_printf("Error! File not found or unable to open.\n");
	return (0);
}
