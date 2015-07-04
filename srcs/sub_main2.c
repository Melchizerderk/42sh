/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_main2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 23:01:06 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 05:22:11 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

static void	sub_exit(t_entry *ent, t_sent **ex)
{
	if ((*ex)->next)
		ent->exit_status = (256 + ft_atoi((*ex)->next->word) % 256) % 256;
	if ((*ex)->next && ((*ex)->next->next || !ft_is_number((*ex)->next->word)))
	{
		write(2, "42sh: exit: Expression Syntax.\n", 31);
		ent->exit_status = 0;
	}
	else if (ent->job && !no_job_stopped(ent->job))
		write(2, "42sh: There are suspended jobs.\n", 32);
	else
	{
		if (ent->job)
			free_job(&ent->job);
		if (ent->par != NULL)
			free_sent(&(ent->par));
		free(ent->save);
		free_sent(ex);
		exit(ent->exit_status);
	}
}

static void	exec_tok(t_entry *ent, t_env **envl, t_sent ***tab)
{
	if (!ft_strncmp((*tab)[0]->word, "|", ft_strlen((*tab)[0]->word)))
		sub_pipe_fork(ent, envl, *tab);
	if (!ft_strncmp((*tab)[0]->word, ">", ft_strlen((*tab)[0]->word)))
		red_right(ent, envl, *tab);
	if (!ft_strncmp((*tab)[0]->word, ">>", ft_strlen((*tab)[0]->word)))
		red_dright(ent, envl, *tab);
	if (!ft_strncmp((*tab)[0]->word, "<", ft_strlen((*tab)[0]->word)))
		red_left(ent, envl, *tab);
	if (!ft_strncmp((*tab)[0]->word, "||", ft_strlen((*tab)[0]->word)))
		or_tok(ent, envl, *tab);
	if (!ft_strncmp((*tab)[0]->word, "&&", ft_strlen((*tab)[0]->word)))
		and_tok(ent, envl, *tab);
	if (!ft_strncmp((*tab)[0]->word, "&", ft_strlen((*tab)[0]->word)))
		jand(ent, envl, *tab);
}

static void	valid_tok(t_entry *ent, t_env **envl, t_sent ***tab)
{
	t_sent	*ex;

	ex = sent_parse(ent->par->word, in_word);
	if (ex && !ft_strncmp(ex->word, "exit", ft_strlen(ex->word)))
		sub_exit(ent, &ex);
	else
	{
		if (ent->par && ent->par->word && ent->par->word[0] != '&')
		{
			*tab = sent_split(sent_parse(ent->par->word, in_word));
			if ((*tab)[0])
				exec_tok(ent, envl, tab);
			else
			{
				if ((ent->pid = fork()) == -1)
					write(2, "42sh: fork error (sub_main2.c).\n", 6);
				if (!(ent->pid))
					ft_son(ent, envl, &((*tab)[1]), &(ent->bin));
				else
					ft_father(ent, envl, &(*tab)[1]);
			}
		}
		else
			write(2, "42sh: parse error near `&'\n", 27);
	}
}

void		sub_main_body(t_entry *ent, t_env **envl)
{
	t_sent	*tmp;
	t_sent	**tab;

	ent->par = NULL;
	tab = NULL;
	tmp = NULL;
	ent->par = NULL;
	if (ent->save != NULL)
	{
		ent->par = sent_parse(ent->save, ft_is_sep);
		while (ent->par)
		{
			if (!parse_tok_error(ent->par->word))
				valid_tok(ent, envl, &tab);
			tmp = ent->par;
			ent->par = ent->par->next;
			if (tmp)
				free(tmp);
			if (tab)
				free_tab(&tab);
		}
	}
}
