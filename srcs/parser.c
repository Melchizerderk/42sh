/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:43:03 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 08:05:27 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

static void	pinit(char **s, size_t (*l)[2], size_t *n_wrd, size_t (*wfct)(char))
{
	(*l)[1] = ft_strlen(*s);
	(*l)[0] = (*l)[1] - 1;
	*n_wrd = nbr_words(*s, wfct);
	while ((*l)[0] > 1 && !wfct((*s)[(*l)[0]]))
		--((*l)[0]);
}

static void	ptail(char **s, t_sent **t, size_t (*l)[2], size_t (*w)(char))
{
	(*t)->word = wjmp(*s, *l, w);
	(*t)->index = (*l)[0];
	(*t)->next = NULL;
	while ((*l)[0] > 1)
	{
		--((*l)[0]);
		*t = add_sent(t, wjmp(*s, *l, w), (*l)[0]);
	}
}

t_sent		*sent_parse(char *str, size_t (*wfct)(char))
{
	t_sent	*tmp;
	size_t	len[2];
	size_t	nbr_of_wrd;

	tmp = NULL;
	pinit(&str, &len, &nbr_of_wrd, wfct);
	if (!wfct(str[len[0]]))
	{
		if (!wfct(str[len[0] - 1]))
			len[1] = len[0] - 1;
		else
			len[1] = len[0];
	}
	else
		len[1] = len[0] + 1;
	len[0] = nbr_of_wrd;
	if ((tmp = (t_sent *)malloc(sizeof(t_sent))) == NULL)
	{
		write(2, "42sh: malloc failed [parser.c]\n", 31);
		return (NULL);
	}
	ptail(&str, &tmp, &len, wfct);
	return (tmp);
}
