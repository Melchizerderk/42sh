/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 17:47:28 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 05:43:31 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

void		ft_echo(t_sent **s)
{
	int	option;

	option = FALSE;
	if (*s)
	{
		if (!ft_strncmp((*s)->word, "-n", ft_strlen((*s)->word)))
		{
			option = TRUE;
			*s = (*s)->next;
		}
		write(1, (*s)->word, ft_strlen((*s)->word));
		*s = (*s ? (*s)->next : *s);
		while (*s && ft_strncmp((*s)->word, ">", ft_strlen((*s)->word)))
		{
			write(1, " ", 1);
			write(1, (*s)->word, ft_strlen((*s)->word));
			*s = (*s)->next;
		}
		*s = (*s ? (*s)->next : *s);
	}
	if (!option)
		write(1, "\n", 1);
	else
		write(2, "\033[7m%\033[0m\n", 10);
}
