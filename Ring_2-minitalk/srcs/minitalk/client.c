/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:18:52 by atang             #+#    #+#             */
/*   Updated: 2023/12/15 16:54:51 by atang            ###   ########.fr       */
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
'send_signal' sends SIGUSR1 (bit set to 1) and SIGUSR2 (bit set to 0) signals 
to a specified process ID (pid) to represent the individual bits of a character.
'bit' is initialised to 0 and used to iterate over each bit of a character 
being sent. While bit is < 8, the bitwise AND operation is used and:
- if the result != 0 (meaning the specific bit in the character is 1), a SIGUSR1 
signal is sent to the pid using the kill function.
- if the bit in the character is 0, a SIGUSR2 signal is sent to the pid using 
the kill function.
'usleep(500)' pauses the program execution for 500 microseconds to control 
the speed at which signals are sent, then bit is incremented to move to the 
next bit of the character until all 8 bits of the character are processed.

N.B (character & (0x01 << bit)) != 0) works to check if a current bit is 1 or 0
by comparison (using the AND operation) against a byte that is all 0's except 
for a 1 in the bit position i.e.

A	B	A & B
0	0	0
0	1	0
1	0	0
1	1	1

where bit = 3, character = 10101010:

     1 0 1 0 1 0 1 0   (character)
   &         1         (0x01 shifted 3 positions)
   ---------------
     0 0 0 0 1 0 0 0   (result of the bitwise AND)
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
pid in converted from a string to an integer using atoi. Then, a signal is sent 
to the specified pid using 'send signal' iterating over each character of the 
message and sending the corresponding signal followed by a new line once out of 
the while loop. An error message is returned if argc != 3.
*/

int	main(int argc, char **argv)
{
	int		i;
	int		pid;

	i = 0;
	if (argc == 3)
	{
		pid = mt_atoi(argv[1]);
		while (argv[2][i] != 0)
		{
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
