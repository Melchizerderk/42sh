/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:43:20 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/09 18:36:33 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

size_t		in_word(char c)
{
	if (c >= '!' && c <= '~')
		return (1);
	return (0);
}

size_t		in_env(char c)
{
	if (c == ':')
		return (0);
	return (1);
}

size_t		ft_is_sep(char c)
{
	if (c == ';')
		return (0);
	return (1);
}
