/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:18:56 by atang             #+#    #+#             */
/*   Updated: 2023/12/15 16:54:48 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
PROGRAM - SERVER
The server program listens to signals ('SIGUSR1' and 'SIGUSR2') from a client.
When 'SIGUSR1' signal is received, it sets individual bits and then prints the 
corresponding character when 8 bits are accumulated to form a byte.
The server program initialises a signal handler using 'sigaction' to catch these
signals and executes the 'handle_signal' function whilst waiting indefinitely
for signals using 'pause()'. 
*/

/*
'handle_signal' accumulates bits received via SIGUSR1 signals.
'info' (additional signal information) and 'context' (program state information)
are used to match the signature required by sigaction when using the 'SA_SIGINFO'
flag but they are unused so they are silenced.
'i' and 'bit' are both static integers which retain their values across function
calls. If signal is SIGUSR1, i is bit-shifted to the left using the bitwise OR 
operator. If 8 bits have been accumulated, the contents of integer 'i' are 
written to the standard output as a single byte. 'Bit' and 'i' are then reset 
to zero to start accumulating bits for the next character from scratch. 

N.B (i |= (0x01 << bit)) works to check if a current bit is 1 or 0
by comparison (using the OR operation) against a byte that is all 0's except 
for a 1 in the bit position i.e.

A	B	A | B
0	0	0
0	1	1
1	0	1
1	1	1

where i = 0, bit = 3,

     0 0 0 0 0 0 0 0   (i in binary)
   |         1         (0x01 shifted 3 positions)
   ---------------
     0 0 0 0 1 0 0 0   (result of the bitwise OR)
*/

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	bit = 0;

	(void)info;
	(void)context;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

/*
The main takes two arguments: argc and argv (argv is cast to 
void to suppress the unused parameter). 'sa', a sigaction structure type, 
is set up to handle signalling behaviour i.e. the action to be taken when
a signal is received. A welcome message, process ID (pid), and 'waiting' 
message are printed. 'sa_flags' is set to SA_SIGINFO, indicating that 
additional information about the signal will be passed to the signal handler. 
The 'sa_sigaction' member of the 'sa' structure is set to 'handle_signal' 
which will be called when a signal is received. The 'sigaction' function is 
then called to set up the signal handlers for SIGUSR1 and SIGUSR2. The 'pause' 
function is then called to pause the program execution until a signal 
is received.
*/

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error!\n");
		return (-1);
	}
	ft_printf("This is Andrew's server\n");
	ft_printf("Server PID is: %d\n", getpid());
	ft_printf("Waiting for message from client...\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
