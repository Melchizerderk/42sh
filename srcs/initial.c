/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 21:00:59 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:59:22 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ftsh.h"

int			ent_init(t_entry *ent, t_env **el, char **av, char **ep)
{
	sub_enti(&ent, av, ep);
	if ((ent->newpwd = (char *)malloc(sizeof(char) * 1024)) == NULL)
		return (0);
	if ((ent->oldpwd = (char *)malloc(sizeof(char) * 1024)) == NULL)
		return (0);
	ent->newpwd = ft_memset(ent->newpwd, '\0', 1024);
	ent->oldpwd = ft_memset(ent->oldpwd, '\0', 1024);
	if (getcwd(ent->oldpwd, 1024) == NULL)
		return (0);
	ent->i = 0;
	ent->job = NULL;
	ent->leaderpid = getpid();
	while (ent->i < 1024)
	{
		ent->newpwd[ent->i] = ent->oldpwd[ent->i];
		++(ent->i);
	}
	if ((*el = (t_env *)malloc(sizeof(t_env))) == NULL)
		return (0);
	return (1);
}

int			envl_init(t_env **el, char **ep)
{
	size_t			i[2];

	i[I] = 0;
	i[J] = 0;
	(*el)->next = NULL;
	(*el)->usr = 0;
	while (ep[i[I]] != NULL)
		++(i[I]);
	i[I] -= (i[I] > 0 ? 1 : 0);
	if (((*el)->ename = (char *)malloc(ft_strlen(ep[i[I]]) + 1)) == NULL)
		return (0);
	while (i[J] < ft_strlen(ep[i[I]]))
	{
		(*el)->ename[i[J]] = ep[i[I]][i[J]];
		++(i[J]);
	}
	i[I] -= (i[I] > 0 ? 1 : 0);
	(*el)->ename[i[I]] = '\0';
	while (i[I] > 0)
		*el = add_envl(el, ep[--i[I] + 1]);
	*el = add_envl(el, ep[I]);
	(*el)->next = (((*el)->next && ((*el)->next->ename[0] == '\0')) ?
					NULL : (*el)->next);
	return (1);
}

void		env_set(t_entry *ent, t_env *envl)
{
	char	**tmp;
	t_env	*save;
	size_t	i;

	i = 0;
	save = envl;
	while (envl != NULL)
	{
		++i;
		envl = envl->next;
	}
	envl = save;
	if ((tmp = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		write(2, "42sh: malloc of ep failed [sub_main.c]\n", 39);
	i = 0;
	while (envl)
	{
		tmp[i] = envl->ename;
		++i;
		envl = envl->next;
	}
	tmp[i] = NULL;
	ent->ep = tmp;
}

void		arg_set(t_entry *ent, t_sent *sent)
{
	char	**tmp;
	t_sent	*save;
	size_t	i;

	i = 0;
	save = sent;
	while (sent != NULL)
	{
		++i;
		sent = sent->next;
	}
	sent = save;
	if ((tmp = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		write(2, "42sh: malloc of av failed [sub_main.c]\n", 39);
	i = 0;
	while (sent)
	{
		tmp[i] = sent->word;
		++i;
		sent = sent->next;
	}
	tmp[i] = NULL;
	ent->av = tmp;
}
