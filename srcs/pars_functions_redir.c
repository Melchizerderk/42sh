/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_functions_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:25:32 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/06 22:47:14 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

size_t		ft_is_redir(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (0);
	return (1);
}

size_t		ft_is_pipe(char c)
{
	if (c == '|')
		return (0);
	return (1);
}

size_t		ft_is_right(char c)
{
	if (c == '>')
		return (0);
	return (1);
}

size_t		ft_is_left(char c)
{
	if (c == '<')
		return (0);
	return (1);
}

size_t		ft_is_inhib(char c)
{
	if (c == '"' || c == '\'')
		return (0);
	return (1);
}
