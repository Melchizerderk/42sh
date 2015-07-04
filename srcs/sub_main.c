/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:41:24 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 00:51:15 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ftsh.h"

static void	sub_set(t_entry **ent)
{
	size_t	i;

	(*ent)->bin = (*ent)->bin_save;
	i = 0;
	while (i < 4096)
	{
		(*ent)->erase[i] = '\0';
		++i;
	}
	i = 0;
	(*ent)->fd = 0;
	(*ent)->end = '\n';
	i = 0;
	(*ent)->save = NULL;
	(*ent)->ret_parse = -1;
	(*ent)->fd = 0;
	(*ent)->pid = -1;
	(*ent)->ret_pipe = -1;
	(*ent)->pfd[IN] = -1;
	(*ent)->pfd[OUT] = -1;
	(*ent)->i = 0;
}

static void	sub_main_sig(void)
{
	signal(SIGCHLD, ft_sighand);
	signal(SIGCONT, ft_sighand);
	signal(SIGHUP, ft_sighand);
	signal(SIGINT, ft_sighand);
	signal(SIGQUIT, ft_sighand);
	signal(SIGTERM, ft_sighand);
	signal(SIGTSTP, ft_sighand);
	signal(SIGTTIN, ft_sighand);
	signal(SIGTTOU, ft_sighand);
	signal(SIGALRM, ft_sighand);
}

int			sub_main(t_entry *ent, t_env **envl)
{
	ent->exit_status = 0;
	ent->job = NULL;
	while (42)
	{
		clean_job(&ent->job);
		if (ent->job)
			ent->job->active = TRUE;
		sub_set(&ent);
		sub_main_sig();
		ft_memset(ent->save, '\0', ft_strlen(ent->save));
		write(1, "\033[2K\033[7D\033[1m\033[35m42sh >\033[0m ", 28);
		if (!sent_fill(ent))
			return (-1);
		if (ent->save && ent->save[0] != '\0' && !ft_inhib(ent)
			&& (ent->ret_parse = parse_error(ent->save, ';', 1)) != -1)
			sub_main_body(ent, envl);
	}
}
