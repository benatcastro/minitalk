/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:43:47 by bena              #+#    #+#             */
/*   Updated: 2022/07/04 11:03:51 by bena             ###   ########.fr       */
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

static int ft_byte_compare(int octet1, int octet2)
{
	int	i;
	int	bit1;
	int bit2;

	i = 8;
	while (i--)
	{
		bit1 = (octet1 >> i & 1);
		bit2 = (octet2 >> i & 1);
		if (bit1 != bit2)
			return (0);
	}
	return (1);
}

static void	ft_signal_handler(int signal, siginfo_t *data, void *ucontext)
{
	static int			i;
	static unsigned		c;
	static pid_t		sender_pid;

	if (!sender_pid)
		sender_pid = data->si_pid;
	(void)ucontext;
	c |= (signal == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			//kill(sender_pid, SIGUSR1);
			sender_pid = 0;
			return ;
		}
		//showbits(c);
		ft_printf("%c", (unsigned char)c);
		c = 0;
		//kill(sender_pid, SIGUSR2);
	}
	else
		c <<= 1;
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	s_action;

	server_pid = getpid();
	ft_printf("SERVER PID: %d\n", server_pid);

	s_action.sa_sigaction = ft_signal_handler;
	sigemptyset (&s_action.sa_mask);
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);

	while (1)
		sleep(100);
	return (1);
}
