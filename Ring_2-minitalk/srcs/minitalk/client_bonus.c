/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:30:39 by sentry            #+#    #+#             */
/*   Updated: 2023/12/15 12:32:36 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
'mt_atoi' is used to convert a string to an integer (process ID aka pid).
*/

int	mt_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

/*
'confirmation' is a static function that takes a signal as an argument
and prints "Message received!" if the signal is SIGUSR2.
*/

static void	confirmation(int sig)
{
	if (sig == SIGUSR2)
		ft_printf ("Message received!\n");
}

/*
'send_signal' is a function that sends a signal to a process identified by pid, 
with the signal corresponding to a character which is sent bit by bit. Using the 
bitwise AND operator, the character is compared to the value of the bit (set to
1) from the LSB (right) to the MSB (left) using a bitmask. If the result != 0, 
the bit is set to 1 and if it is == 0 it means the bit as the current position 
is not set (i.e 0). If the bit is 1, the SIGUSR1 signal is sent and if the bit 
is 0, the SIGUSR2 signal is sent, looping through each bit of the character and
sending the appropriate signal. It waits for 500 microseconds before sending 
the next bit.
*/

void	send_signal(int pid, unsigned char character)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((character & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

/*
The main takes two arguments: the pid and the message. If argc == 3, the 
pid in converted from a string to an integer using atoi. Then, signal handlers 
are registered for SIGUSR1 and SIGUR2 and a signal is sent to the specified pid
using 'send signal' iterating over each character of the message and sending the 
corresponding signal followed by a new line once out of the while loop. An error
message is returned if argc != 3.
*/

int	main(int argc, char **argv)
{
	int		i;
	int		pid;

	i = 0;
	if (argc == 3)
	{
		pid = mt_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			signal(SIGUSR1, confirmation);
			signal(SIGUSR2, confirmation);
			send_signal (pid, argv[2][i]);
			i++;
		}
		send_signal(pid, '\n');
	}
	else
	{
		ft_printf("Error!\nCorrect format is: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	return (0);
}
