/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:57:15 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/17 15:12:14 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// int main(int ac, char **av)
// {
// 	if (ac < 3)
// 	{
// 		fprintf(stderr, "usage: %s DELAY STRING\n", av[0]);
// 		return 1;
// 	}
// 	printf("%s: my pid is %d\n", av[0], getpid());

// 	int delay = atoi(av[1]);
// 	int counter = 1;

// 	while (1)
// 	{
// 		sleep(delay);
// 		printf("[%d] %d %s\n", getpid(), counter++, av[2]);
// 	}
// }

void handler(int n)
{
	char msg[] = "got signal\n";
	write(STDOUT_FILENO, &msg, sizeof(msg) - 1);
}

int main(int ac, char **av)
{
	if (ac < 3)
	{
		fprintf(stderr, "usage: %s DELAY STRING\n", av[0]);
		return 1;
	}
	struct sigaction sa = {};
	sa.sa_handler = handler;
	// sa.sa_handler = SIG_IGN;
	// sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	int delay = atoi(av[1]);
	int counter = 1;

	while (1)
	{
		sleep(delay);
		printf("[%d] %d %s\n", getpid(), counter++, av[2]);
	}
}