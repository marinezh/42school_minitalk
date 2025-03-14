/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:39:36 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/03/14 13:46:23 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void send_char(pid_t server_pid, char ch) {
    for (int i = 7; i >= 0; i--) { // Send each bit (MSB first)
        if (ch & (1 << i)) {
            kill(server_pid, SIGUSR1);  // Send bit 1
        } else {
            kill(server_pid, SIGUSR2);  // Send bit 0
        }
        usleep(50000);  // Delay to allow the server to process the signal
    }
}

int main() {
    pid_t server_pid;
    char ch;

    printf("Enter server PID: ");
    scanf("%d", &server_pid);

    printf("Enter a single character: ");
    scanf(" %c", &ch);

    send_char(server_pid, ch);

    return 0;
}