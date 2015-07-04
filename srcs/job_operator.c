/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 16:03:31 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 03:05:24 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/stat.h"
#include "sys/resource.h"
#include "sys/wait.h"
#include "ftsh.h"

static void jand_result(t_entry *ent)
{
	write(1, "[", 1);
	ft_putnbr_off_t(ent->job->number, 1);
	write(1, "] ", 2);
	ft_putnbr_off_t(ent->job->pid, 1);
	write(1, "\n", 1);
	write(1, "\033[1m\033[35m42sh >\033[0m\n", 20);
	if (WIFSTOPPED(ent->pid))
	{
		write(1, "[", 1);
		ft_putnbr_off_t(ent->job->number, 1);
		write(1, "] + suspended\t(tty output)\t", 27);
		write(1, ent->job->command, ft_strlen(ent->job->command));
		write(1, "\n", 1);
		ent->job->stopped = TRUE;
	}
	else
	{
		write(1, "\n[", 2);
		ft_putnbr_off_t(ent->job->number, 1);
		write(1, "] + done\t", 9);
		write(1, ent->job->command, ft_strlen(ent->job->command));
		write(1, "\n", 1);
	}
}

static void	jand_father(t_entry *ent, t_sent **tab)
{
	int		son_pid;
	t_job	*save;

	save = NULL;
	if ((son_pid = waitpid(ent->pid, &ent->pid, WUNTRACED)) == -1)
		write(2, "42sh: waitpid failed [job_operator.c]\n", 38);
	ent->job = add_job(ent->job, tab[1], son_pid);
	save = ent->job;
	while (ent->job && ent->job->next)
		ent->job = ent->job->next;
	if (ent->job)
		jand_result(ent);
	ent->job = save;
}

void		jand(t_entry *ent, t_env **envl, t_sent **tab)
{
	if (!tab[1])
		write(2, "42sh: parse error near `&'\n", 27);
	else
	{
		if (ent->job)
			ent->job->active = FALSE;
		if ((ent->pid = fork()) == -1)
			write(2, "42sh: Error\n", 12);
		if (!(ent->pid))
		{
			setpriority(PRIO_PROCESS, (id_t)getpid(), 5);
			umask(0);
			ft_son(ent, envl, &(tab[1]), &(ent->bin));
		}
		else
			jand_father(ent, tab);
	}
}
