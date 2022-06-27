/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:30:26 by bena              #+#    #+#             */
/*   Updated: 2022/06/28 01:26:30 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "signal.h"

static int ft_check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid[i] && (ft_isdigit(pid[i]) != 0 || pid[i] == '-'))
		i++;
	if (i != (int)ft_strlen(pid))
		return (0);
	else
		return (1);
}
int main(int argc, char	*argv[])
{
	int	pid;


	if (argc == 1)
	{
		ft_printf ("usage ./client.exec [Server-PID] [String to send]\n");
		exit (1);
	}
	else if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_printf("Please enter the PID of the process and the string to send.\n");
		exit (1);
	}
	pid = ft_atoi(argv[1]);
	(void)pid;
	if (!ft_check_pid(argv[1]))
	{
		ft_printf("Wrong PID, try again please.\n");
		exit (1);
	}
	pid = ft_atoi(argv[1]);
}
