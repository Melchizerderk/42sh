/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_me.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 21:15:26 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 06:07:04 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ftsh.h"

static void	sub_sigchld(void)
{
	int		fd;
	int		pid;

	pid = getpid();
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	fd = open("/dev/tty", O_RDONLY);
	ioctl(fd, TIOCSPGRP, &pid);
	close(fd);
}

void		ft_sighand(int sig)
{
	if (sig == SIGCHLD)
		sub_sigchld();
	if (sig == SIGINT)
		write(1, "\033[2D\033[K\n\033[1m\033[35m42sh >\033[0m ", 28);
	if (sig == SIGTSTP)
		write(1, "\033[2D\033[K\007", 8);
	if (sig == SIGHUP)
	{
		write(1, "\033[7m%\033[0m\n", 10);
		exit(1);
	}
	if (sig == SIGALRM)
	{
		write(1, "\n42sh: timeout\n", 15);
		exit(0);
	}
	if (sig == SIGQUIT)
		write(1, "\033[2D\033[K\007", 8);
}
