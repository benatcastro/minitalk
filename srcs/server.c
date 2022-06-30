/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:43:47 by bena              #+#    #+#             */
/*   Updated: 2022/06/30 15:01:08 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"


void	showbits(unsigned char x )
{
	int	i;

	i = 0;
	for (i = (sizeof(char) * 8) - 1; i >= 0; i--)
	{
		putchar(x & (1u << i) ? '1' : '0');
	}
	printf("\n");
}
static void ft_send_confirmation()
{

}

static void	ft_print_byte(int data)
{
	static int	i;
	char		c;

	if (data == -1)
	{
		//ft_printf("\n");
		//showbits(c);
		ft_printf("%c", c);
		c <<= 8;
		i = 0;
		//ft_printf("\nFinished");
	}
	else
	{
		if (data == 1)
			c |= (1 << (7 - i));
		else if (data == 0)
			c |= (0 << (7 - i));
		i++;
		//ft_printf("%d", data->si_int);
	}
}

static void	ft_signal_handler(int signal, siginfo_t *data, void *ucontext)
{

	(void)ucontext;
	if (signal == SIGUSR1)
	{
		if (data->si_int == 2)
			ft_printf("[SERVER]Recieving from (%d):[", data->si_pid);
		else if (data->si_int == 3)
			ft_printf("]\n");
		else
			ft_print_byte(data->si_int);
	}
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	signal_action;

	server_pid = getpid();
	printf("SERVER PID: %d\n", server_pid);

	signal_action.sa_sigaction = ft_signal_handler;
	sigemptyset (&signal_action.sa_mask);
	signal_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_action, NULL);

	while (1)
		sleep(100);
	return (1);
}
