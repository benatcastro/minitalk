/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:43:47 by bena              #+#    #+#             */
/*   Updated: 2022/07/04 16:08:41 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"

static unsigned char	*ft_append_char(unsigned char *str, char c)
{
	unsigned char	*result;
	unsigned int	len;

	len = -1;
	while (str[++len])
		continue ;

	result = malloc(len + 2);
	ft_ustrlcpy(result, str, len);
	free(str);
	ft_printf("Append result: (%s)\n", result);
	result[len + 1] = c;
	result[len + 2] = '\0';
	return (result);
}

static void	ft_print_message(pid_t pid, unsigned char c)
{
	unsigned char	*message;

	message = malloc(0);

	if (c == 2)
		ft_printf("[SERVER] Recieved message[");
	else if (c == 3)
		ft_printf("] from (%d)\n", pid);
	else
		ft_append_char(message, c);

}

static void	ft_signal_handler(int signal, siginfo_t *data, void *ucontext)
{
	static int				i;
	static unsigned char	c;

	(void)ucontext;
	c |= (signal == SIGUSR2);

	if (++i == 8)
	{
		if (!c)
		{
			kill(data->si_pid, SIGUSR2);
			return ;
		}
		ft_print_message(data->si_pid, c);
		i = 0;
		c = 0;
		kill(data->si_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	s_action;

	server_pid = getpid();
	ft_printf("[SERVER]Started on pid (%d)\n", server_pid);
	s_action.sa_sigaction = ft_signal_handler;
	sigemptyset (&s_action.sa_mask);
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);

	while (1)
		pause();
	return (1);
}
