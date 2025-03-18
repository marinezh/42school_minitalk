/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:54:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/18 12:36:04 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		is_flag = 0;

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
		if (!is_flag)
			usleep(100);
		is_flag = 0;
		bit++;
	}
}

void	handle_ack(int sig)
{
	(void)sig;
	// write(1, "Ack\n", 4);
	// printf("Acknowledgment received from server\n");
	is_flag = 1;
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	int		i;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = atoi(argv[1]);
	// Register signal handler for acknowledgment
	signal(SIGUSR1, handle_ack);
	// Send message character by character
	i = 0;
	printf("Sending message to server (PID %d): %s\n", server_pid, argv[2]);
	while (argv[2][i] != '\0')
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
