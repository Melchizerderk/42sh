/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:44:21 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 06:13:14 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include "ftsh.h"

static void	tail_father(t_entry *ent, t_env **envl, t_sent **sent, int status)
{
	if (!ft_strncmp((*sent)->word, "setenv", ft_strlen((*sent)->word)))
		sub_fathset(envl, sent);
	else if (!ft_strncmp((*sent)->word, "unsetenv", ft_strlen((*sent)->word)))
		sub_fathun(envl, sent);
	else if (!ft_strncmp((*sent)->word, "cd", ft_strlen((*sent)->word)))
		sub_fathcd(ent, envl, sent);
	else if (!ft_strncmp((*sent)->word, "fg", ft_strlen((*sent)->word)))
		sub_fathfg(ent, sent);
	else if (!ft_strncmp((*sent)->word, "bg", ft_strlen((*sent)->word)))
		sub_fathbg(ent, sent);
	else if (!ft_strncmp((*sent)->word, "jobs", ft_strlen((*sent)->word)))
		sub_fathjob(ent, sent);
	if (WIFSTOPPED(status))
	{
		if (ent->job)
			ent->job->active = FALSE;
	}
}

static void	core_father(t_entry *ent, t_sent **sent, int son_pid, int status)
{
	t_job	*save;

	save = NULL;
	ent->job = add_job(ent->job, *sent, son_pid);
	if (ent->job)
		ent->job->status = status;
	if (WIFSTOPPED(status))
		write(1, "\n42sh: suspended\n", 17);
	if (ent->job && WIFSTOPPED(status))
		ent->job->active = FALSE;
	if (ent->job && !ent->job->active)
	{
		save = ent->job;
		while (ent->job && ent->job->next)
			ent->job = ent->job->next;
		if (ent->job)
			ent->job->stopped = TRUE;
		ent->job = save;
	}
	ent->exit_status = WEXITSTATUS(status);
}

void		ft_father(t_entry *ent, t_env **envl, t_sent **sent)
{
	int		son_pid;
	int		status;
	int		pid;
	int		fd;

	pid = getpid();
	status = ent->pid;
	setpgid(ent->pid, ent->pid);
	fd = open("/dev/tty", O_RDONLY);
	ioctl(fd, TIOCSPGRP, &ent->pid);
	son_pid = waitpid(ent->pid, &status, WUNTRACED);
	ioctl(fd, TIOCSPGRP, &pid);
	close(fd);
	core_father(ent, sent, son_pid, status);
	arg_set(ent, *sent);
	tail_father(ent, envl, sent, status);
}
