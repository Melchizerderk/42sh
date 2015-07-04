/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:41:15 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/08 15:42:20 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

static void	unset_last(t_env **e, t_env **save)
{
	char	**last_ep;

	last_ep = NULL;
	if ((last_ep = (char **)malloc(sizeof(char *))) != NULL)
	{
		if ((last_ep[0] = (char *)malloc(sizeof(char))) != NULL)
		{
			last_ep[0] = NULL;
			free(*e);
			*e = NULL;
			if ((*e = (t_env *)malloc(sizeof(t_env))) != NULL)
			{
				envl_init(e, last_ep);
				*save = *e;
			}
		}
	}
}

static void	sub_unset(t_env **e, t_env **tmp, t_env **prev, t_env **save)
{
	if (*e != NULL)
	{
		*tmp = *e;
		if (*e == *save)
		{
			*e = (*e)->next;
			if (!*e)
				unset_last(e, save);
			else
				*save = *e;
			free(*tmp);
		}
		else
		{
			*e = *prev;
			(*e)->next = (*tmp)->next;
			free(*tmp);
		}
	}
	else
		write(2, "Nonexistent variable\n", 21);
}

void		ft_unsetenv(t_env **e, t_sent *s)
{
	t_env	*save;
	t_env	*prev;
	t_env	*tmp;
	int		cmp;

	save = *e;
	prev = *e;
	while (*e && !((*e)->ename))
		*e = (*e)->next;
	if (*e)
	{
		cmp = ft_strncmp((*e)->ename, s->word, ft_strlen(s->word));
		while (*e != NULL && cmp != 0)
		{
			prev = *e;
			*e = (*e)->next;
			while (*e && !((*e)->ename))
				*e = (*e)->next;
			if (*e != NULL)
				cmp = ft_strncmp((*e)->ename, s->word, ft_strlen(s->word));
		}
		sub_unset(e, &tmp, &prev, &save);
	}
	*e = save;
}
