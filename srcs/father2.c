/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 04:27:24 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 03:55:42 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

void	sub_fathset(t_env **envl, t_sent **sent)
{
	*sent = (*sent)->next;
	ft_setenv(envl, *sent);
}

void	sub_fathun(t_env **envl, t_sent **sent)
{
	if ((*sent)->next != NULL)
	{
		*sent = (*sent)->next;
		ft_unsetenv(envl, *sent);
	}
}

void	sub_fathcd(t_entry *ent, t_env **envl, t_sent **sent)
{
	*sent = (*sent)->next;
	ft_cd(ent, *envl, *sent);
}
