/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imdumb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 18:58:15 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:55:13 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

t_pars			is_tok(char *str)
{
	if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (PIPE);
	if (!ft_strncmp(str, ">", ft_strlen(str)))
		return (RIGHT);
	if (!ft_strncmp(str, ">>", ft_strlen(str)))
		return (DRIGHT);
	if (!ft_strncmp(str, "<", ft_strlen(str)))
		return (LEFT);
	if (!ft_strncmp(str, "<<", ft_strlen(str)))
		return (DLEFT);
	if (!ft_strncmp(str, "&&", ft_strlen(str)))
		return (AND);
	if (!ft_strncmp(str, "||", ft_strlen(str)))
		return (OR);
	if (!ft_strncmp(str, "&", ft_strlen(str)))
		return (ESPERL);
	return (NONE);
}

static t_sent	**tab_init(t_sent *sent, size_t *sent_len)
{
	t_sent	**tmp;
	t_sent	*save;

	save = sent;
	*sent_len = 0;
	while (sent)
	{
		++(*sent_len);
		sent = sent->next;
	}
	sent = save;
	if ((tmp = (t_sent **)malloc(sizeof(t_sent) * (*sent_len + 2))) == NULL)
	{
		write(2, "42sh: malloc failed [imdumb.c]\n", 31);
		return (NULL);
	}
	tmp[0] = NULL;
	return (tmp);
}

static int		htab_fill(t_sent **sent, t_sent ***tab, size_t *j)
{
	if (*sent)
	{
		++(*j);
		if ((*tab)[0])
			add_rev_sent(&(*tab)[0], (*sent)->word);
		else
		{
			if (((*tab)[0] = (t_sent *)malloc(sizeof(t_sent))) == NULL)
			{
				write(2, "42sh: malloc failed [imdumb.c]\n", 31);
				return (1);
			}
			(*tab)[0]->word = (*sent)->word;
			(*tab)[0]->index = 1;
			(*tab)[0]->next = NULL;
		}
		*sent = (*sent)->next;
	}
	return (0);
}

static int		tab_fill(t_sent **sent, t_sent ***tab, size_t *i, size_t *j)
{
	while (*sent && is_tok((*sent)->word) != NONE)
	{
		if (htab_fill(sent, tab, j))
			return (1);
	}
	if (!*sent)
	{
		(*tab)[*i] = NULL;
		return (0);
	}
	(*tab)[*i]->word = (*sent)->word;
	(*tab)[*i]->index = 1;
	(*tab)[*i]->next = NULL;
	if (*sent)
	{
		++(*j);
		*sent = (*sent)->next;
	}
	while (*sent && is_tok((*sent)->word) == NONE)
	{
		add_rev_sent(&(*tab)[*i], (*sent)->word);
		++(*j);
		*sent = (*sent)->next;
	}
	return (0);
}

t_sent			**sent_split(t_sent *sent)
{
	t_sent		**tab;
	size_t		sent_len;
	size_t		i;
	size_t		j;

	i = 1;
	j = 0;
	tab = NULL;
	if ((tab = tab_init(sent, &sent_len)) == NULL)
		return (NULL);
	while (j < sent_len)
	{
		if ((tab[i] = (t_sent *)malloc(sizeof(t_sent))) == NULL)
		{
			write(2, "42sh: malloc failed [imdumb.c]\n", 31);
			return (NULL);
		}
		if (tab_fill(&sent, &tab, &i, &j))
			return (NULL);
		if (htab_fill(&sent, &tab, &j))
			return (NULL);
		++i;
	}
	tab[i] = NULL;
	return (tab);
}
