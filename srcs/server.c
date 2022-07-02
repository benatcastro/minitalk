/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:43:47 by bena              #+#    #+#             */
/*   Updated: 2022/07/02 03:15:56 by bena             ###   ########.fr       */
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
	int8_t		c;

	if (i < 8)
	{
		if (data == 1)
			c |= (1 << (7 - i));
		else if (data == 0)
			c |= (0 << (7 - i));
		i++;
	}
	if (i == 8)
	{
		//ft_printf("\n");
		//showbits(c);
		ft_printf("CHAR: %c\n", c);
		c <<= 8;
		i = 0;
		//ft_printf("\nFinished");
	}
		//ft_printf("test %d\n", i);
}

static void	ft_signal_handler(int signal, siginfo_t *data, void *ucontext)
{

	(void)ucontext;
	if (signal == SIGUSR1)
	{
		//ft_printf("[SERVER]Recieved bit: (0)\n");
		ft_print_byte(0);
	}
	else if (signal == SIGUSR2)
	{
		//ft_printf("[SERVER]Recieved bit: (1)\n");
		ft_print_byte(1);
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
	sigaction(SIGUSR2, &signal_action, NULL);

	while (1)
		sleep(100);
	return (1);
}
