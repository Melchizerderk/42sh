/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 17:51:15 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/23 15:37:59 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

void		free_envl(t_env **envl)
{
	while (*envl)
	{
		free(*envl);
		*envl = (*envl)->next;
	}
}

void		free_sent(t_sent **sent)
{
	t_sent	*save;

	save = *sent;
	while (*sent)
	{
		if ((*sent)->word)
			free((*sent)->word);
		(*sent)->word = NULL;
		*sent = (*sent)->next;
	}
	*sent = save;
	while (*sent)
	{
		free(*sent);
		*sent = (*sent)->next;
	}
}

void		free_tab(t_sent ***tab)
{
	size_t	i;

	i = 1;
	if ((*tab)[0])
		free_sent(&((*tab)[0]));
	while ((*tab)[i])
	{
		free_sent(&((*tab)[i]));
		++i;
	}
	free(*tab);
	*tab = NULL;
}
