/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:30:26 by bena              #+#    #+#             */
/*   Updated: 2022/07/02 03:03:56 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "signal.h"

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
static void	ft_send(pid_t pid, int8_t data)
{
	int				bit;
	int				i;

	i = 8;
	while (i--)
	{
		bit = (data >> i & 1);
		if (bit == 0)
			kill(pid, SIGUSR1);
		else if (bit == 1)
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

/*Send the entire string to the designed PID
CODES:
2: Indicates the start of a new string transmission
3: Indicates the end of the of string transmission*/

static void	ft_send_string(pid_t pid, char *str)
{
	union sigval	code;
	int				i;

	i = -1;
	usleep(100);
	while (str[++i])
		ft_send(pid, str[i]);
}

static void	ft_signal_handler(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("[CLIENT] Server recieved the package");
}

int	main(int argc, char	*argv[])
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = ft_check_args(argv[1], argc, argv);
	ft_send_string(pid, argv[2]);
	signal(SIGUSR2, ft_signal_handler);
}
