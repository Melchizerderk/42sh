/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:45:44 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/03 14:19:40 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

void		cmdnf(t_sent *sent)
{
	write(2, "42sh: ", 6);
	write(2, sent->word, ft_strlen(sent->word));
	write(2, ": command not found\n", 20);
}

int			arg_error(int ac, char **av)
{
	if (ac != 1)
	{
		write(1, "Problem with ", 13);
		write(1, av[1], ft_strlen(av[1]));
		write(1, "\n42sh cannot work with arguments.\n", 34);
		return (1);
	}
	return (0);
}

static int	sub_parse_error(char *s, char c, size_t max, size_t i)
{
	size_t	doub;

	doub = 0;
	while (i < ft_strlen(s) && doub < max + 1)
	{
		if (s[i] == c)
			++doub;
		else
			doub = 0;
		++i;
	}
	if (doub == (max + 1))
	{
		write(2, "42sh : parse error near `", 25);
		i = 0;
		write(2, &c, 1);
		if (c == ';')
			write(2, &c, 1);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}

int			parse_error(char *s, char c, size_t max)
{
	size_t	i;

	i = 0;
	if (!sub_parse_error(s, c, max, i))
		return (-1);
	return (1);
}

int			parse_tok_error(char *s)
{
	if (parse_error(s, '|', 2) == -1)
		return (1);
	if (parse_error(s, '>', 2) == -1)
		return (1);
	if (parse_error(s, '<', 2) == -1)
		return (1);
	if (parse_error(s, '&', 2) == -1)
		return (1);
	return (0);
}
