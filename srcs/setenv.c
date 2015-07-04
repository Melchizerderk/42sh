/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:42:09 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 08:07:21 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

static int	sub_set_init(t_sent **s, t_env **t, char **k, char **v)
{
	if (*s == NULL)
		return (0);
	if ((*t = (t_env *)malloc(sizeof(t_env))) == NULL)
	{
		write(2, "42sh: malloc failed [building.c]\n", 33);
		return (0);
	}
	*k = (*s)->word;
	*s = (*s)->next;
	if (*s != NULL)
		*v = (*s)->word;
	(*t)->ename = ft_strjoin(*k, *v, '=');
	(*t)->usr = 1;
	(*t)->next = NULL;
	return (1);
}

static void	sub_set(t_env **envl, t_env **tmp, char *key)
{
	if ((*envl)->ename && !ft_strncmp((*envl)->ename, key, ft_strlen(key)))
	{
		(*envl)->ename = (*tmp)->ename;
		free_envl(tmp);
	}
	else
		(*envl)->next = *tmp;
}

void		ft_setenv(t_env **envl, t_sent *sent)
{
	t_env	*save;
	t_env	*tmp;
	char	*key;
	char	*value;

	tmp = NULL;
	key = NULL;
	value = NULL;
	save = *envl;
	if (sub_set_init(&sent, &tmp, &key, &value))
	{
		while ((*envl)->next != NULL && (!(*envl)->ename
				|| ft_strncmp((*envl)->ename, key, ft_strlen(key))))
			*envl = (*envl)->next;
		sub_set(envl, &tmp, key);
		*envl = save;
	}
	else
	{
		if (tmp)
			free_envl(&tmp);
	}
}
