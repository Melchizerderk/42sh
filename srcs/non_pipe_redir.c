/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_pipe_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:43:37 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 05:27:39 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "ftsh.h"

void		red_right(t_entry *ent, t_env **envl, t_sent **tab)
{
	if (!tab[1])
		write(2, "42sh: parse error near `\\n'\n", 28);
	else if (!tab[2])
		write(2, "42sh: not supported\n", 20);
	else
	{
		if ((ent->pid = fork()) == -1)
			write(2, "42sh: Error\n", 12);
		if (!(ent->pid))
		{
			if ((ent->ret_popen = open(tab[2]->word,
				O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			{
				write(2, "42sh: error with the file\n", 26);
				exit(0);
			}
			dup2(ent->ret_popen, 1);
			ft_son(ent, envl, &tab[1], &(ent->bin));
		}
		else
			ft_father(ent, envl, &(tab[1]));
	}
}

void		red_dright(t_entry *ent, t_env **envl, t_sent **tab)
{
	if (!tab[1])
		write(2, "42sh: parse error near `\\n'\n", 28);
	else if (!tab[2])
		write(2, "42sh: not supported\n", 20);
	else
	{
		if ((ent->pid = fork()) == -1)
			write(2, "42sh: Error\n", 12);
		if (!(ent->pid))
		{
			if ((ent->ret_popen = open(tab[2]->word,
				O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			{
				write(2, "42sh: error with the file\n", 26);
				exit(0);
			}
			dup2(ent->ret_popen, 1);
			ft_son(ent, envl, &tab[1], &(ent->bin));
		}
		else
			ft_father(ent, envl, &(tab[1]));
	}
}

void		and_tok(t_entry *ent, t_env **envl, t_sent **tab)
{
	if (!tab[1])
		write(2, "42sh: parse and error\n", 22);
	else if (!tab[2])
		write(2, "42sh: parse and error\n", 22);
	else
	{
		if ((ent->pid = fork()) == -1)
			write(2, "42sh: Error\n", 16);
		if (!(ent->pid))
			ft_son(ent, envl, &tab[1], &(ent->bin));
		else
			ft_father(ent, envl, &tab[1]);
		if (ent->exit_status == 0)
		{
			if ((ent->pid = fork()) == -1)
				write(2, "42sh: Error\n", 12);
			if (!ent->pid)
				ft_son(ent, envl, &tab[2], &(ent->bin));
			else
				ft_father(ent, envl, &tab[2]);
		}
	}
}

void		or_tok(t_entry *ent, t_env **envl, t_sent **tab)
{
	if (!tab[1])
		write(1, "42sh: parse or error\n", 21);
	else if (!tab[2])
		write(1, "42sh: parse or error\n", 21);
	else
	{
		if ((ent->pid = fork()) == -1)
			write(2, "42sh: Error\n", 12);
		if (!(ent->pid))
			ft_son(ent, envl, &tab[1], &(ent->bin));
		else
			ft_father(ent, envl, &tab[1]);
		if (ent->exit_status != 0)
		{
			if ((ent->pid = fork()) == -1)
				write(2, "42sh: Error\n", 12);
			if (!ent->pid)
				ft_son(ent, envl, &tab[2], &(ent->bin));
			else
				ft_father(ent, envl, &tab[2]);
		}
	}
}
