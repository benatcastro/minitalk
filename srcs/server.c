/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:43:47 by bena              #+#    #+#             */
/*   Updated: 2022/06/28 23:03:37 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"

void	signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	if (siginfo->si_int == -1)
		ft_printf("\nFinished");
	else
		ft_printf("%d", siginfo->si_int);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	struct sigaction signal_action;

	server_pid = getpid();
	printf("SERVER PID: %d\n", server_pid);

	signal_action.sa_sigaction = signal_handler;
	sigemptyset (&signal_action.sa_mask);
	signal_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_action, NULL);

	while(1) sleep(100);
	return EXIT_SUCCESS;
}
