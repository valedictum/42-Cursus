/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:48:16 by sentry            #+#    #+#             */
/*   Updated: 2023/12/15 16:54:50 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
'handle_signal' accumulates bits received via SIGUSR1 signals.
'info' (additional signal information) and 'context' (program state information)
are used to match the signature required by sigaction when using the 'SA_SIGINFO'
flag but they are unused so they are silenced.
'i' and 'bit' are both static integers which retain their values across function
calls. If signal is SIGUSR1, i is bit-shifted to the left using the bitwise OR 
operator. If 8 bits have been accumulated, the contents of integer 'i' are 
written to the standard output as a single byte. 'Bit' and 'i' are then reset 
to zero to start accumulating bits for the next character from scratch. The kill
function is then used to send the SIGUSR2 signal to the specified pid which 
ultimately results in 'Message received!' being printed as a confirmation.
*/

void	handle_signal_b(int signal, siginfo_t *info, void *context)
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
		kill(info->si_pid, SIGUSR2);
	}
}

/*
The main takes two arguments: argc and argv (argv is cast to 
void to suppress the unused parameter). sigaction structure type 'sa' 
is set up to handle signalling behaviour i.e. the action to be taken when
a signal is received. A welcome message, process ID (pid), and 'waiting' 
message are printed. 
The 'sa_sigaction' member of the 'sa' structure is set to 'handle_signal'
which will be called when a signal is received. 'sigemptyset(&sa.sa_mask)'
sets the sa_mask member to an empty set ensuring that the signal handler
can safely execute without being interrupted by other signals. 'sa_flags' 
is set to SA_SIGINFO indicating that additional information about the signal 
will be passed to the signal handler. The 'sigaction' function is then called
to set up the signal handlers for SIGUSR1 and SIGUSR2. The 'pause' function is 
then called to pause the program execution until a signal is received.
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
	ft_printf("This is Andrew's BONUS server\n");
	ft_printf("Server PID is: %d\n", getpid());
	ft_printf("Waiting for message from client...\n");
	sa.sa_sigaction = handle_signal_b;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
