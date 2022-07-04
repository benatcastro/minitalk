/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:30:26 by bena              #+#    #+#             */
/*   Updated: 2022/07/04 10:37:43 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"

static pid_t	ft_check_args(char *pid, int argc, char *argv[])
{
	int	i;

	if (argc == 1)
	{
		ft_printf ("usage ./client.exec [Server-PID] [String to send]\n");
		exit (1);
	}
	else if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_printf(
			"Please enter the PID of the process and the string to send.\n");
		exit (1);
	}
	i = 0;
	while (pid[i] && (ft_isdigit(pid[i]) != 0 || pid[i] == '-'))
		i++;
	if (i != (int)ft_strlen(pid))
	{
		ft_printf("Wrong PID, try again please.\n");
		exit (1);
	}
	else
		return ((pid_t)ft_atoi(pid));
}

/*Converts the char into bits and send them to indicated PID
Codes:
-1 indicates that the octet of bytes is finished*/
static void	ft_send(pid_t pid, char data)
{
	int					i;

	i = 8;
	while (i--)
	{
		if (data >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
	if ((int)data == -1)
	{
		i = 8;
		while (i--)
		{
			kill(pid, SIGUSR1);
			usleep(100);
		}
	}
}

/*Send the entire string to the designed PID
CODES:
2: Indicates the start of a new string transmission
3: Indicates the end of the of string transmission*/

static void	ft_send_string(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_send(pid, str[i]);
		i++;
	}
	ft_send(pid, -1);
}

static void	ft_signal_handler(int signal, siginfo_t *data, void *ucontext)
{
	(void)ucontext;
	ft_printf("[CLIENT] Server (%d) recieved the package\n", data->si_pid);
}

int	main(int argc, char	*argv[])
{
	pid_t				pid;
	int					i;
	struct sigaction	s_action;

	i = -1;
	pid = ft_check_args(argv[1], argc, argv);
	ft_send_string(pid, argv[2]);
	//ft_send(pid, -1);
}
