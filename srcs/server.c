/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:43:47 by bena              #+#    #+#             */
/*   Updated: 2022/07/05 02:22:24 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"
#include <string.h>

// static unsigned char	*ft_append_char(unsigned char *str, unsigned char c)
// {
// 	unsigned char	*result;
// 	int				i;

// 	ft_printf("STR (%s) C (%c))\n", str, c);
// 	result = malloc(ft_ustrlen(str) + 2 * sizeof(unsigned char));
// 	i = -1;
// 	while (str[++i] && i < (int)ft_ustrlen(str))
// 		result[i] = str[i];
// 	ft_printf("I: (%d)\n", i);
// 	result[i] = c;
// 	result[i + 1] = 0;
// 	//free(str);
// 	return (result);

// }

static void	ft_print_message(pid_t pid, unsigned char c)
{
	unsigned char			*message;
	static unsigned char	*aux;
	static unsigned int		i;

	ft_printf("\n-----CHAR (%c)-----\n", c);
	message = ft_calloc(i + 1, (sizeof(unsigned char)));
	if (aux)
		message = ft_ustrdup(aux);
	if (c == 2)
		ft_printf("[SERVER] Recieved message[");
	else if (c == 4)
	{
		ft_printf("\n====TEST====\n");
		ft_printf("%s] from (%d)\n", message, pid);
		free(message);
		aux = 0;
		i = 0;
	}
	else
	{
		ft_printf("\ntest\n");
		message[i] = c;
		message[i + 1] = 0;
		ft_printf("\nMESSAGE (%s)\n", message);
		aux = ft_ustrdup(message);
		ft_printf("\nAUX (%s)\n", aux);
		free(message);
		i++;
	}

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
