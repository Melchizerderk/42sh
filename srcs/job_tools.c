/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 15:48:18 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:16:43 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

int			no_job_stopped(t_job *job)
{
	while (job)
	{
		if (job->stopped)
			return (0);
		job = job->next;
	}
	return (1);
}

int			ft_is_number(char *str)
{
	size_t	i;

	i = 1;
	if (!str)
		return (1);
	if ((str[0] < '0' || str[0] > '9') && str[0] != '-')
		return (0);
	while (i < ft_strlen(str) && str[i] >= '0' && str[i] <= '9')
		++i;
	if (str[i] != '\0' || (str[0] == '-' && i == 1 && str[i] == '\0'))
		return (0);
	return (1);
}

static void	core_add_job(t_job **job, t_job *save, char *command, int pid)
{
	t_job	*tmp;

	if ((tmp = (t_job *)malloc(sizeof(t_job))) != NULL)
	{
		tmp->pid = pid;
		tmp->command = command;
		tmp->number = ((*job != NULL) ? (*job)->number + 1 : 1);
		tmp->active = TRUE;
		tmp->stopped = FALSE;
		tmp->next = NULL;
		if (*job)
		{
			(*job)->next = tmp;
			*job = save;
		}
		else
			*job = tmp;
	}
}

t_job		*add_job(t_job *job, t_sent *sent, int pid)
{
	char	*command;
	t_job	*save;
	t_sent	*sent_save;

	command = NULL;
	sent_save = NULL;
	save = job;
	sent_save = sent;
	while (sent)
	{
		command = ft_strjoin(command, sent->word, ' ');
		sent = sent->next;
	}
	sent = sent_save;
	while (job && job->next)
		job = job->next;
	core_add_job(&job, save, command, pid);
	return (job);
}
