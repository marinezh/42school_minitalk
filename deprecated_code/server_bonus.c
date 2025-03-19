/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:53:27 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/19 23:19:26 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	process_character(char character)
{
	static char	message[BUFFER_SIZE];
	static int	msg_index = 0;

	if (character == '\0') // End of message
	{
		message[msg_index] = '\0'; // Null-terminate the buffer
		write(1, message, ft_strlen(message));
		write(1, "\n", 1); // Optional: Add newline for readability
		msg_index = 0;     // Reset buffer for the next message
	}
	else
	{
		if (msg_index < BUFFER_SIZE - 1) // Avoid buffer overflow
			message[msg_index++] = character;
	}
}
void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_pos = 0;
	static char	character = 0;

	(void)context;
	if (sig == SIGUSR2)
		character |= (1 << bit_pos); // SIGUSR2 means bit 1
	bit_pos++;
	if (bit_pos == 8) // Completed a character
	{
		process_character(character);
		// If the message ended, notify client
		if (character == '\0')
		{
			kill(info->si_pid, SIGUSR2); // Final ACK
			bit_pos = 0;
			character = 0;
			return ; // Stop, no need to ack bit-level anymore
		}
		bit_pos = 0;
		character = 0;
	}
	// Acknowledge each bit so the client continues
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
	ft_printf("Server started. PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
