/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:30:04 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/10 16:46:28 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

int	main(int argv, char **av)
{
	
	int pid = fork();
	if (pid == -1)
		return 1;
	if(pid == 0)
	{
		while(1)
		{
			printf("some text goes here\n");
			usleep(50000);
		}
	}
	else
	{
		sleep(1);
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return (0);
}