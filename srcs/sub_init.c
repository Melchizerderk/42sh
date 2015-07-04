/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:41:39 by mngomane          #+#    #+#             */
/*   Updated: 2014/05/30 22:49:10 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

void		sub_enti(t_entry **ent, char **av, char **ep)
{
	(*ent)->av = av;
	(*ent)->ep = ep;
	(*ent)->save = NULL;
	(*ent)->ano_buf[0] = '\0';
	(*ent)->ano_buf[1] = '\0';
	(*ent)->ret_parse = -1;
	(*ent)->fd = 0;
	(*ent)->pid = -1;
	(*ent)->ret_pipe = -1;
	(*ent)->pfd[IN] = -1;
	(*ent)->pfd[OUT] = -1;
	(*ent)->end = '\n';
	(*ent)->newpwd = NULL;
	(*ent)->oldpwd = NULL;
}
