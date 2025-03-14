/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:53:27 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/14 15:02:21 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_pos = 0;
	static char	character = 0;

	(void)context; // Unused parameter
	// If SIGUSR1 is received, bit = 0; If SIGUSR2, bit = 1
	if (sig == SIGUSR1)
		character |= (0 << bit_pos);
	else if (sig == SIGUSR2)
		character |= (1 << bit_pos);
	bit_pos++;
	// When we have 8 bits, print the character
	if (bit_pos == 8)
	{
		write(1, &character, 1);
		bit_pos = 0;
		character = 0;
	}
	// Send acknowledgment back to client
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	// Get server PID
	printf("Server PID: %d\n", getpid());
	// Set up signal handler
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// Keep server running
	while (1)
		pause();
	return (0);
}
