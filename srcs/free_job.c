/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 15:33:32 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 08:11:10 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

void		delet_job(t_job **job, int pid)
{
	t_job	*save;

	save = *job;
	if (*job && (*job)->pid == pid)
	{
		if ((*job)->command)
			free((*job)->command);
		free(*job);
		*job = (*job)->next;
		save = *job;
	}
	else
	{
		while (*job && (*job)->next && (*job)->next->pid != pid)
			*job = (*job)->next;
		if (*job && (*job)->next)
		{
			if ((*job)->command)
				free((*job)->command);
			free((*job)->next);
			(*job)->next = (*job)->next->next;
			*job = save;
		}
	}
}

static int	no_active_job(t_job *job)
{
	while (job)
	{
		if (!job->stopped)
			return (0);
		job = job->next;
	}
	return (1);
}

void		clean_job(t_job **job)
{
	t_job	*save;

	while (!no_active_job(*job))
	{
		save = *job;
		if (!(*job)->stopped)
		{
			if ((*job)->command)
				free((*job)->command);
			free(*job);
			*job = (*job)->next;
			save = *job;
		}
		else if ((*job)->next)
			clean_job(&((*job)->next));
		*job = save;
	}
}

void		free_job(t_job **job)
{
	while (*job)
	{
		if ((*job)->command)
			free((*job)->command);
		free(*job);
		*job = (*job)->next;
	}
}
