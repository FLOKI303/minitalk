/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:12:39 by aait-mal          #+#    #+#             */
/*   Updated: 2022/12/21 14:32:56 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sigusr_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 7;
	static int				pid_sender;

	(void) context;
	if (!pid_sender)
		pid_sender = info->si_pid;
	if (pid_sender != info->si_pid)
	{
		c = 0;
		i = 7;
		pid_sender = info->si_pid;
	}
	if (signum == SIGUSR1)
		c |= (1 << i);
	if (i == 0)
	{
		i = 7;
		ft_printf("%c", c);
		c = 0;
	}
	else
		i--;
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	action.sa_sigaction = sigusr_handler;
	action.sa_flags = SA_SIGINFO;
	pid = getpid();
	if (sigaction(SIGUSR1, &action, NULL) < 0)
		return (1);
	if (sigaction(SIGUSR2, &action, NULL) < 0)
		return (1);
	ft_printf("%d\n", pid);
	while (1)
		pause();
	return (0);
}
