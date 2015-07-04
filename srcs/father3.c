/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 03:55:13 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 03:55:50 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

void	sub_fathbg(t_entry *ent, t_sent **sent)
{
	*sent = (*sent)->next;
	ft_bg(ent, *sent);
}

void	sub_fathfg(t_entry *ent, t_sent **sent)
{
	*sent = (*sent)->next;
	ft_fg(ent, *sent);
}

void	sub_fathjob(t_entry *ent, t_sent **sent)
{
	*sent = (*sent)->next;
	ft_job(ent, *sent);
}
