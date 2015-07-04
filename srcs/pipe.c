/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:42:37 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/08 16:26:13 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

static void	sub_fork_it(t_entry *ent, t_env **envl, t_sent **tab, int pfd[2])
{
	if ((ent->son_pid = fork()) == -1)
	{
		write(1, "42sh: Error\n", 12);
		exit(0);
	}
	if (!ent->son_pid)
	{
		close(pfd[IN]);
		dup2(pfd[OUT], 1);
		ft_son(ent, envl, &tab[1], &(ent->bin));
	}
	else
	{
		close(pfd[OUT]);
		dup2(pfd[IN], 0);
		ft_son(ent, envl, &tab[2], &(ent->bin));
	}
}

void		sub_pipe_fork(t_entry *ent, t_env **envl, t_sent **tab)
{
	int		ret_pipe;
	int		pfd[2];

	ret_pipe = -1;
	pfd[IN] = -1;
	pfd[OUT] = -1;
	if (!tab[1] || !tab[2])
		write(2, "42sh: parse pipe error\n", 23);
	else
	{
		if ((ent->pid = fork()) == -1)
			write(2, "Error\n", 6);
		if (!(ent->pid))
		{
			if ((ret_pipe = pipe(pfd)) == -1)
			{
				write(2, "42sh: pipe error\n", 17);
				exit(0);
			}
			sub_fork_it(ent, envl, tab, pfd);
		}
		else
			ft_father(ent, envl, &(tab[1]));
	}
}
