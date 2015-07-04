/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:43:52 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 08:03:22 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

t_env			*add_envl(t_env **envl, char *ename)
{
	t_env	*tmp;

	if ((tmp = (t_env *)malloc(sizeof(t_env))) != NULL)
	{
		tmp->ename = ename;
		tmp->usr = 0;
		tmp->next = (*envl);
	}
	else
		write(2, "42sh: malloc in add_envl failed [list_edit.c]\n", 46);
	return (tmp);
}

t_sent			*add_sent(t_sent **sent, char *word, size_t i)
{
	t_sent	*tmp;

	if ((tmp = (t_sent *)malloc(sizeof(t_sent))) != NULL)
	{
		tmp->word = word;
		tmp->index = i;
		tmp->next = *sent;
	}
	else
		write(2, "malloc in add_sent failed\n", 26);
	return (tmp);
}

void			add_rev_sent(t_sent **sent, char *word)
{
	t_sent	*tmp;
	t_sent	*save;

	save = NULL;
	if ((tmp = (t_sent *)malloc(sizeof(t_sent))) != NULL)
	{
		tmp->word = word;
		tmp->index = (*sent)->index + 1;
		tmp->next = NULL;
		save = *sent;
		while (*sent && (*sent)->next)
			*sent = (*sent)->next;
		if (*sent)
			(*sent)->next = tmp;
		else
			*sent = tmp;
		if (save)
			*sent = save;
	}
	else
		write(2, "42sh: malloc in add_sent failed [list_edit.c]\n", 46);
}

t_bin			*add_bin(t_bin **bin, char *path)
{
	t_bin		*tmp;

	if ((tmp = (t_bin *)malloc(sizeof(t_bin))) != NULL)
	{
		tmp->path = path;
		tmp->next = *bin;
	}
	else
		write(2, "42sh: malloc in add_bin failed [list_edit.c]\n", 45);
	return (tmp);
}
