/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:46:25 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 08:08:56 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

size_t		nbr_words(char *str, size_t (*wfct)(char))
{
	size_t	nbr_wrd;
	size_t	letter[2];
	size_t	len;
	size_t	i;

	i = 0;
	letter[0] = 0;
	letter[1] = 0;
	nbr_wrd = 0;
	len = ft_strlen(str);
	if (str != NULL)
	{
		while (i < len)
		{
			letter[0] = letter[1];
			letter[1] = wfct(str[i]);
			if (!letter[0] && letter[1])
				++nbr_wrd;
			++i;
		}
	}
	return (nbr_wrd);
}

static void	sjmp(t_jmp *var, char *s, size_t l[2], size_t (*w)(char))
{
	size_t	secure;

	if (s != NULL)
	{
		var->letter[1] = 0;
		secure = 0;
		while (++secure < READ_MAX + 1 && var->i < READ_MAX && var->i < l[1]
				&& var->wrd < l[0])
		{
			var->letter[0] = var->letter[1];
			var->letter[1] = w(s[var->i]);
			var->wrd += ((!var->letter[0] && var->letter[1]) ? 1 : 0);
			if (var->wrd < l[0] && var->i < l[1] && s[var->i] != '\0')
				++(var->i);
		}
		secure = 0;
		var->save = var->i;
		while (++secure < READ_MAX + 1 && var->i < l[1] && var->letter[1])
		{
			var->letter[0] = var->letter[1];
			var->letter[1] = w(s[var->i]);
			if (var->letter[1] && var->i < l[1] && s[var->i] != '\0')
				++(var->i);
		}
	}
}

char		*wjmp(char *s, size_t l[2], size_t (*w)(char))
{
	t_jmp	var;

	var.i = 0;
	var.wrd = 0;
	var.save = 0;
	sjmp(&var, s, l, w);
	var.len_word = var.i - var.save;
	var.i = var.save;
	var.wrd = var.i;
	if ((var.tmp = (char *)malloc(sizeof(char) * (var.len_word + 1))) == NULL)
	{
		write(2, "42sh: malloc failed [parser2.c]\n", 32);
		return (NULL);
	}
	while (var.i < READ_MAX && w(s[var.i]) && (var.i - var.wrd) < var.len_word)
	{
		var.tmp[var.i - var.wrd] = s[var.i];
		++(var.i);
	}
	var.tmp[var.i - var.wrd] = '\0';
	return (var.tmp);
}
