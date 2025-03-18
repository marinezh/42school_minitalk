/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:54:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/18 19:22:50 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	ack_received = 0;

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1) // if the bit is 1
		{
			// printf("Sending bit 1 for character '%c'\n", c);
			kill(server_pid, SIGUSR2); // Send 1
		}
		else if (!((c >> bit) & 1)) // if the bit is 0
		{
			// printf("Sending bit 0 for character '%c'\n", c);
			kill(server_pid, SIGUSR1); // Send 0
		}
		if (!ack_received)
			pause();
		ack_received = 0;
		bit++;
	}
}

void	handle_ack(int sig)
{
	(void)sig;
	// write(1, "Ack\n", 4);
	// printf("Acknowledgment received from server\n");
	ack_received = 1;
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = atoi(argv[1]);
	// Register signal handler for acknowledgment
	if (server_pid == 0 || kill(server_pid, 0))
	{
		printf("Process with this id doesn't exist\n");
		return (1);
	}
	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);

	// Send message character by character
	i = 0;
	printf("Sending message to server (PID %d): %s\n", server_pid, argv[2]);
	while (argv[2][i] != '\0')
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
	// if (sigaction(SIGUSR1, &sa, NULL) == -1)
	// {
	// 	perror("sigaction");
	// 	return (1);
	// }