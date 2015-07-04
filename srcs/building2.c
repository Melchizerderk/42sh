/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 04:38:38 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/22 19:07:46 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "ftsh.h"

static void	error_job(t_sent *sent)
{
	write(2, "jobs: job not found: ", 21);
	write(2, sent->word, ft_strlen(sent->word));
	write(2, "\n", 1);
}

static void	sub_job(t_entry *ent, t_sent *sent, t_job **save, int *job_nbr)
{
	*job_nbr = ft_atoi(sent->word);
	while (ent->job && ent->job->number != *job_nbr)
		ent->job = ent->job->next;
	if (ent->job && ent->job->number == *job_nbr && ent->job->stopped)
	{
		write(1, "[", 1);
		ft_putnbr_off_t(ent->job->number, 1);
		write(1, "] - continued\t", 14);
		write(1, ent->job->command, ft_strlen(ent->job->command));
		write(1, "\n", 1);
		ent->job = *save;
	}
	else
	{
		ent->job = *save;
		write(2, "jobs: %", 7);
		ft_putnbr_off_t((off_t)(*job_nbr), 2);
		write(2, ": no such job\n", 14);
	}
}

static void	core_job(t_entry *ent, t_sent *sent, t_job **save, int *job_nbr)
{
	++(sent->word);
	if (sent->word && !ft_strncmp(sent->word, "%", ft_strlen(sent->word)))
	{
		if (ent->job)
		{
			write(1, "[", 1);
			ft_putnbr_off_t(ent->job->number, 1);
			write(1, "] - continued\t", 14);
			write(1, ent->job->command, ft_strlen(ent->job->command));
			write(1, "\n", 1);
		}
	}
	else if (ft_is_number(sent->word))
		sub_job(ent, sent, save, job_nbr);
	else
	{
		ent->job = *save;
		error_job(sent);
	}
	--(sent->word);
}

static void	no_arg_job(t_entry *ent, t_job **save)
{
	while (ent->job)
	{
		if (ent->job->stopped)
		{
			write(1, "[", 1);
			ft_putnbr_off_t(ent->job->number, 1);
			write(1, "]  suspended\t", 13);
			write(1, ent->job->command, ft_strlen(ent->job->command));
			write(1, "\n", 1);
		}
		ent->job = ent->job->next;
	}
	ent->job = *save;
}

void		ft_job(t_entry *ent, t_sent *sent)
{
	t_job	*save;
	int		job_nbr;

	save = ent->job;
	job_nbr = 0;
	if (!sent)
		no_arg_job(ent, &save);
	else
	{
		while (sent && sent->word)
		{
			if (sent->word[0] == '%')
				core_job(ent, sent, &save, &job_nbr);
			else
				error_job(sent);
			sent = sent->next;
		}
	}
}
