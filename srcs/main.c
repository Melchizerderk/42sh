/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:46:02 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 08:04:13 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ftsh.h"

int				path_init(t_entry *ent)
{
	if ((ent->bin = (t_bin *)malloc(sizeof(t_bin))) != NULL)
	{
		ent->bin->path = "/usr/texbin";
		ent->bin->next = NULL;
		ent->bin = add_bin(&(ent->bin), "/opt/X11/bin");
		ent->bin = add_bin(&(ent->bin), "/sbin");
		ent->bin = add_bin(&(ent->bin), "/usr/sbin");
		ent->bin = add_bin(&(ent->bin), "/bin");
		ent->bin = add_bin(&(ent->bin), "/usr/bin");
		ent->bin = add_bin(&(ent->bin), "/usr/local/bin");
		ent->bin_save = ent->bin;
	}
	else
	{
		write(2, "42sh: malloc failed [main.c]\n", 29);
		return (0);
	}
	return (1);
}

int				main(int ac, char **av, char **envp)
{
	t_entry		ent;
	t_env		*envl;

	if (!isatty(0))
	{
		write(2, "\033[31m42sh:\033[0m thanks to not redirect stdin...\n", 47);
		return (-1);
	}
	if (arg_error(ac, av))
		return (-1);
	if (!path_init(&ent))
		return (-1);
	if (!ent_init(&ent, &envl, av, envp))
		return (-1);
	if (!envl_init(&envl, envp))
		return (-1);
	if (!sub_main(&ent, &envl))
		return (-1);
	return (0);
}
