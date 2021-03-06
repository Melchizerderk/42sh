/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 06:10:27 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:39:03 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include "ftsh.h"

static void	launch_fg(t_entry *ent)
{
	int		fd;
	int		status;

	status = 0;
	write(1, "[", 1);
	ft_putnbr_off_t(ent->job->number, 1);
	write(1, "] - continued\t", 14);
	write(1, ent->job->command, ft_strlen(ent->job->command));
	write(1, "\n", 1);
	ent->job->stopped = FALSE;
	fd = open("/dev/tty", O_RDONLY);
	if (ioctl(fd, TIOCSPGRP, &ent->job->pid) == 0)
		kill(ent->job->pid, SIGCONT);
	close(fd);
	waitpid(ent->job->pid, &status, WUNTRACED);
	if (WIFSTOPPED(status))
		ent->job->stopped = TRUE;
}

static void	num_fg(t_entry *ent, t_sent *sent, t_job **save, int job_nbr)
{
	job_nbr = ft_atoi(sent->word);
	while (ent->job && ent->job->number != job_nbr)
		ent->job = ent->job->next;
	if (ent->job && ent->job->number == job_nbr && ent->job->stopped)
	{
		launch_fg(ent);
		ent->job = *save;
	}
	else
	{
		ent->job = *save;
		write(2, "fg: %", 5);
		ft_putnbr_off_t((off_t)job_nbr, 2);
		write(2, ": no such job\n", 14);
	}
}

static void	core_fg(t_entry *ent, t_sent *sent, t_job **save, int job_nbr)
{
	++(sent->word);
	if (sent->word && sent->word[0] == '%')
	{
		*save = ent->job;
		while (ent->job && ent->job->next && ent->job->next->stopped)
			ent->job = ent->job->next;
		if (ent->job)
			launch_fg(ent);
		ent->job = *save;
	}
	else if (ft_is_number(sent->word))
		num_fg(ent, sent, save, job_nbr);
	else
	{
		ent->job = *save;
		write(2, "fg: job not found: ", 19);
		write(2, sent->word, ft_strlen(sent->word));
		write(2, "\n", 1);
	}
	--(sent->word);
}

static void	sub_fg(t_entry *ent, t_sent *sent, t_job **save, int job_nbr)
{
	while (sent && sent->word)
	{
		if (sent->word[0] == '%')
			core_fg(ent, sent, save, job_nbr);
		else
		{
			write(2, "fg: job not found: ", 19);
			write(2, sent->word, ft_strlen(sent->word));
			write(2, "\n", 1);
		}
		sent = sent->next;
	}
}

void		ft_fg(t_entry *ent, t_sent *sent)
{
	t_job	*save;
	int		job_nbr;

	save = ent->job;
	job_nbr = 0;
	if (ent->job && !no_job_stopped(ent->job))
	{
		if (!sent)
		{
			save = ent->job;
			while (ent->job && ent->job->next && ent->job->next->stopped)
				ent->job = ent->job->next;
			if (ent->job)
				launch_fg(ent);
			ent->job = save;
		}
		else
			sub_fg(ent, sent, &save, job_nbr);
	}
	else
		write(1, "fg: No current job.\n", 20);
}
