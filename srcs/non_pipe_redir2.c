/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_pipe_redir2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/05 21:11:57 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/09 19:46:50 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "ftsh.h"

static void	sub_lred(t_entry *ent, t_sent **tab)
{
	t_sent	*sent;

	sent = NULL;
	if ((ent->ret_popen = open(tab[1]->word, O_RDONLY)) == -1)
	{
		write(2, "42sh: no such file or directory: ", 33);
		write(2, tab[1]->word, ft_strlen(tab[1]->word));
		write(2, "\n", 1);
		exit(1);
	}
	if ((sent = (t_sent *)malloc(sizeof(sizeof(t_sent)))) == NULL)
		exit (1);
	sent->word = "more";
	sent->index = 1;
	sent->next = tab[1];
	ent->av = (char **)malloc(sizeof(char *) * 3);
	ent->av[0] = "more";
	ent->av[1] = tab[1]->word;
	ent->av[2] = NULL;
	execve("/usr/bin/more", ent->av, ent->ep);
}

void		red_left(t_entry *ent, t_env **envl, t_sent **tab)
{
	if (!tab[1])
		write(2, "42sh: parse error near `\\n'\n", 28);
	else
	{
		if ((ent->pid = fork()) == -1)
			write(2, "Error\n", 6);
		if (!(ent->pid))
		{
			if (tab[2])
			{
				if ((ent->ret_popen = open(tab[2]->word, O_RDONLY)) == -1)
				{
					write(2, "42sh: no such file or directory: ", 33);
					write(2, tab[2]->word, ft_strlen(tab[2]->word));
					write(2, "\n", 1);
					exit(1);
				}
				ft_son(ent, envl, &tab[1], &(ent->bin));
			}
			sub_lred(ent, tab);
			exit(0);
		}
		else
			waitpid(0, &(ent->pid), WUNTRACED);
	}
}
