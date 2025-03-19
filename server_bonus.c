/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:53:27 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/19 13:53:26 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_pos = 0;
	static char	character = 0;

	(void)context;
	if (sig == SIGUSR2)
		character |= (1 << bit_pos); // Set bit to 1 if SIGUSR2 received
	bit_pos++;
	if (bit_pos == 8) // After receiving 8 bits, print the character
	{
		if (character != '\0')
			write(1, &character, 1);
		else
			write(1, "\n", 1);
		bit_pos = 0;
		character = 0;
	}
	// Send acknowledgment to client after processing the bit
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction sa; // struct to handle signal actions
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// Keep server running
	printf("Server started. PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
