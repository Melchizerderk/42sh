/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:45:30 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/24 20:54:59 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include "ftsh.h"

int			ft_env(t_env *envl)
{
	while (envl)
	{
		write(1, envl->ename, ft_strlen(envl->ename));
		write(1, "\n", 1);
		envl = envl->next;
	}
	return (1);
}

static void	check_right(char *word)
{
	if (access(word, X_OK) == -1)
	{
		write(2, "42sh: permission denied: ", 25);
		write(2, word, ft_strlen(word));
		write(2, "\n", 1);
		exit (126);
	}
}

static void	exec_right(t_entry *ent, char *word)
{
	struct stat	filestat;

	if (!access(word, F_OK))
	{
		if (stat(word, &filestat) == 0 && filestat.st_uid != 0)
		{
			if (word[0] == '.' && word[1] == '/')
				check_right(word);
		}
		else
			check_right(word);
		execve(word, ent->av, ent->ep);
	}
}

void		exec_cmd(t_entry *ent, t_sent *sent, t_bin *b)
{
	if (ent->av != NULL && ent->ep != NULL)
	{
		while (b != NULL)
		{
			exec_right(ent, ft_strjoin(b->path, sent->word, '/'));
			b = b->next;
		}
		exec_right(ent, sent->word);
	}
}
