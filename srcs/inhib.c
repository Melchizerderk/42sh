/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 15:13:20 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:56:35 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

static void	inhib_save_fill(char *str, char *save, size_t (*var)[5])
{
	while ((*var)[I] < ft_strlen(str))
	{
		if (str[(*var)[I]] == '"' && (*var)[BSLASH] == FALSE
			&& !((*var)[SQUOTE] % 2))
			++(*var)[DQUOTE];
		else if (str[(*var)[I]] == '\'' && (*var)[BSLASH] == FALSE
				&& !((*var)[DQUOTE] % 2))
			++(*var)[SQUOTE];
		else if (str[(*var)[I]] == '\\')
		{
			if ((*var)[I] > 0 && (*var)[BSLASH] == TRUE
				&& str[(*var)[I] + 1] != '/' && str[(*var)[I] + 1] != '"'
				&& str[(*var)[I] + 1] != '\'' && str[(*var)[I] - 1] == '\\')
				save[++(*var)[J] - 1] = str[(*var)[I]];
			(*var)[BSLASH] = ((*var)[BSLASH] ? FALSE : TRUE);
		}
		else
		{
			save[(*var)[J]] = str[(*var)[I]];
			++(*var)[J];
			(*var)[BSLASH] = FALSE;
		}
		++(*var)[I];
	}
	save[(*var)[J]] = '\0';
}

static int	core_inhib(char *str, char *save, size_t (*var)[5])
{
	inhib_save_fill(str, save, var);
	if ((*var)[SQUOTE] % 2)
	{
		write(1, "Unmatched \'.\n", 13);
		return (1);
	}
	if ((*var)[DQUOTE] % 2)
	{
		write(1, "Unmatched \".\n", 13);
		return (1);
	}
	return (0);
}

int			ft_inhib(t_entry *ent)
{
	char	*save;
	char	*str;
	size_t	var[5];

	if (ent->save == NULL)
		return (1);
	if ((save = (char *)malloc(sizeof(char) * ft_strlen(ent->save))) == NULL)
	{
		write(2, "42sh: malloc failed [inhib.c]\n", 30);
		return (1);
	}
	str = ent->save;
	var[I] = 0;
	var[J] = 0;
	var[BSLASH] = FALSE;
	var[SQUOTE] = 0;
	var[DQUOTE] = 0;
	if (core_inhib(str, save, &var))
		return (1);
	free(ent->save);
	ent->save = save;
	return (0);
}
