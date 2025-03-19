/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:54:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/19 23:27:05 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	ack_received = 0;

void	handle_ack(int sig)
{
	if (sig == SIGUSR1)
		ack_received = 1;
	else if (sig == SIGUSR2)
	{
		printf("✅ Server received and printed the whole message ✅\n");
		exit(0);
	}
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		ack_received = 0;
		if ((c >> bit) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		bit++;
		while (!ack_received)
			pause();
	}
}

int	pid_validation(char *str)
{
	int	server_pid;
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf("Error: Process ID must be numeric\n");
			exit(1);
		}
		i++;
	}
	server_pid = ft_atoi(str);
	if (server_pid <= 1)
	{
		ft_printf("Error: PID %d is invalid.\n", server_pid);
		exit(1);
	}
	if (kill(server_pid, 0) == -1)
	{
		ft_printf("Error: Process %d does not exist.\n", server_pid);
		exit(1);
	}
	return (server_pid);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = pid_validation(argv[1]);
	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	pause();
	return (0);
}
