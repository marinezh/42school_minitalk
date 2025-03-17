/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:54:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/17 14:40:14 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_char(pid_t server_pid, char c)
{
	int bit  = 8;

	while (bit--)
	{
		if ((c >> bit) & 1)
			kill(server_pid, SIGUSR2); // Send 1
		else
			kill(server_pid, SIGUSR1); // Send 0
		usleep(100);
	}
}

void handle_ack(int sig)
{
	(void)sig;
	//write(1, "Ack\n", 4);
}

int main(int argc, char *argv[])
{
	pid_t server_pid;
	int i;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return 1;
	}

	server_pid = atoi(argv[1]);

	// Register signal handler for acknowledgment
	signal(SIGUSR1, handle_ack);

	// Send message character by character
	for (i = 0; argv[2][i] != '\0'; i++)
		send_char(server_pid, argv[2][i]);

	return 0;
}
