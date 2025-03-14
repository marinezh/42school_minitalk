/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:40:11 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/14 13:53:13 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

     char received_char = 0;
    int bit_count = 0;


void signal_handler(int signum)
{

    
    if (signum == SIGUSR1) {
        received_char = (received_char << 1) | 1;  // Append 1
    } else if (signum == SIGUSR2) {
        received_char = (received_char << 1) | 0;  // Append 0
    }
    
    bit_count++;

    if (bit_count == 8) {  // 8 bits received (1 byte = 1 char)
        printf("Received character: %c\n", received_char);
        received_char = 0;
        bit_count = 0;
    }
}

int main() {
    printf("Server PID: %d\n", getpid());

    // Register signal handlers
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    // Keep server running
    while (1)
    {
        pause(); // Wait for signals
    }

    return 0;
}