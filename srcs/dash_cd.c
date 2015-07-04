/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:44:55 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:49:03 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

void		dash_cd(t_entry *ent)
{
	size_t	i;

	i = 0;
	if (ent->oldpwd != NULL)
	{
		if (ent->oldpwd[0] != '\0')
		{
			ent->oldpwd = ft_memset(ent->oldpwd, '\0', 1024);
			if (getcwd(ent->oldpwd, 1024) == NULL)
				write(2, "42sh: getcwd failed [dash_cd]\n", 30);
			if (chdir(ent->newpwd) == -1)
				write(2, "42sh: chdir failed [dash_cd]\n", 29);
			write(1, ent->newpwd, ft_strlen(ent->newpwd));
			write(1, "\n", 1);
			while (i < 1024)
			{
				ent->newpwd[i] = ent->oldpwd[i];
				++i;
			}
		}
	}
}
