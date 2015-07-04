/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   son.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:46:39 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 05:49:04 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ftsh.h"

static int	cmd_valid(t_entry *ent, t_sent **sent)
{
	if (!ft_strncmp((*sent)->word, "exit", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp((*sent)->word, "cd", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp((*sent)->word, "echo", ft_strlen((*sent)->word)))
	{
		*sent = (*sent)->next;
		ft_echo(sent);
		return (1);
	}
	if (!ft_strncmp((*sent)->word, "setenv", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp((*sent)->word, "unsetenv", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp((*sent)->word, "bg", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp((*sent)->word, "fg", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp((*sent)->word, "jobs", ft_strlen((*sent)->word)))
		return (1);
	if (!ft_strncmp(ent->save, "", ft_strlen(ent->save)))
		return (1);
	return (0);
}

static int	exec_son(t_sent **s)
{
	if (!ft_strncmp((*s)->word, "unsetenv", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "setenv", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "echo", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "exit", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "cd", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "bg", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "fg", ft_strlen((*s)->word)))
		return (0);
	else if (!ft_strncmp((*s)->word, "jobs", ft_strlen((*s)->word)))
		return (0);
	return (1);
}

static void	sub_son(t_entry *ent, t_sent **s, t_bin **b)
{
	if (exec_son(s))
		exec_cmd(ent, *s, *b);
	if (!cmd_valid(ent, s))
	{
		cmdnf(*s);
		free(ent->save);
		ent->save = NULL;
	}
	else
		exit(0);
	free_sent(s);
}

static void	core_son(t_entry *ent, t_env **el, t_sent **s, t_bin **b)
{
	if (!ft_strncmp(ent->save, "env", ft_strlen(ent->save)))
	{
		if (ft_env(*el))
		{
			free(ent->save);
			ent->save = NULL;
			free_sent(s);
			exit(0);
		}
	}
	else
	{
		sub_son(ent, s, b);
		exit(127);
	}
}

void		ft_son(t_entry *ent, t_env **el, t_sent **s, t_bin **b)
{
	int		pid;
	int		fd;

	if ((setpgid(0, 0)))
		write(2, "42sh: setpgid() failed\n", 23);
	pid = getpid();
	fd = open("/dev/tty", O_RDONLY);
	ioctl(fd, TIOCSPGRP, &pid);
	close(fd);
	arg_set(ent, *s);
	core_son(ent, el, s, b);
}
