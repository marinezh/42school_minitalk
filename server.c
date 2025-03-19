/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:53:27 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/19 23:35:15 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	process_character(char character)
{
	static char	message[BUFFER_SIZE];
	static int	msg_index = 0;

	if (character == '\0')
	{
		message[msg_index] = '\0';
		write(1, message, ft_strlen(message));
		write(1, "\n", 1);
		msg_index = 0;
	}
	else
	{
		if (msg_index < BUFFER_SIZE - 1)
			message[msg_index++] = character;
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_pos;
	static char	character;

	(void)context;
	if (sig == SIGUSR2)
		character |= (1 << bit_pos);
	bit_pos++;
	if (bit_pos == 8)
	{
		process_character(character);
		bit_pos = 0;
		character = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server started. PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
