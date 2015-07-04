/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:45:11 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:46:17 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

static void	new_wdir(t_entry *ent)
{
	ent->newpwd = ft_memset(ent->newpwd, '\0', 1024);
	if (getcwd(ent->newpwd, 1024) == NULL)
		write(2, "42sh: getcwd failed [cd.c]\n", 27);
}

static void	home_cd(t_env **envl)
{
	if ((*envl)->ename)
	{
		(*envl)->home = ft_strncmp((*envl)->ename, "HOME=", 5);
		while ((*envl)->home != 0 && (*envl)->next != NULL)
		{
			*envl = (*envl)->next;
			(*envl)->home = ft_strncmp((*envl)->ename, "HOME=", 5);
		}
	}
}

static void	sub_cd(t_entry *ent, t_sent *sent)
{
	new_wdir(ent);
	if (chdir(sent->word) == -1)
	{
		if (sent->next)
		{
			write(2, "cd: string not in pwd: ", 23);
			write(2, sent->word, ft_strlen(sent->word));
			write(2, "\n", 1);
		}
		else
		{
			write(2, "cd: no such file or directory: ", 31);
			write(2, sent->word, ft_strlen(sent->word));
			write(2, "\n", 1);
		}
	}
}

static void	backup_cd(char *cdpath)
{
	cdpath -= 5;
	if (cdpath)
		cdpath += 5;
	else
		cdpath = "(null)";
	write(2, "42sh: Problem with HOME path: ", 30);
	write(2, cdpath, ft_strlen(cdpath));
	write(2, ".\nRoot is your new directory.\n", 30);
	chdir("/");
}

void		ft_cd(t_entry *ent, t_env *envl, t_sent *sent)
{
	char	*cdpath;

	cdpath = NULL;
	if (envl)
	{
		home_cd(&envl);
		if (!(envl->home))
		{
			cdpath = envl->ename;
			cdpath += 5;
			if (sent)
			{
				if (!ft_strncmp(sent->word, "-", ft_strlen(sent->word)))
					dash_cd(ent);
				else
					sub_cd(ent, sent);
			}
			else
			{
				new_wdir(ent);
				if (chdir(cdpath) == -1)
					backup_cd(cdpath);
			}
		}
	}
}
