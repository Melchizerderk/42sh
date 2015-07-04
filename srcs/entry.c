/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:44:39 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/25 07:51:57 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include "ftsh.h"

int			secu_malloc(char **str, size_t len)
{
	if ((*str = (char *)malloc(sizeof(char) * len)) == NULL)
	{
		write(2, "42sh: malloc failed [entry.c]\n", 30);
		return (0);
	}
	return (1);
}

static char	*sub_trim(char *str, char *tmp, size_t len, size_t i)
{
	if ((tmp = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
	{
		write(2, "42sh: malloc failed [entry.c]\n", 30);
		return (NULL);
	}
	i = 0;
	while (i < READ_MAX && i < len)
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = '\0';
	return (tmp);
}

char		*trim_entry(char *str, size_t (*wfct)(char))
{
	char		*tmp;
	size_t		i;
	size_t		len;

	tmp = NULL;
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	while (!wfct(*str) && *str != '\0')
	{
		++str;
		--len;
	}
	if (len > 0)
		i = len - 1;
	else
		return (NULL);
	while (!wfct(str[i]) && i > 1)
	{
		--i;
		--len;
	}
	tmp = sub_trim(str, tmp, len, i);
	return (tmp);
}

static int	sub_fill(t_entry *ent, char (*buffer)[READ_MAX + 1], ssize_t *ret)
{
	size_t		i;

	i = 0;
	(*buffer)[*ret] = '\0';
	if (*ret == READ_MAX + 1)
	{
		write(2, "File name too long !\n", 21);
		while ((*ret = read(ent->fd, ent->erase, 4096)) >= 0\
				&& ent->erase[4095] != 0)
			;
		return (1);
	}
	if (ent->save != NULL)
		free(ent->save);
	if (!secu_malloc(&(ent->save), (size_t)(*ret) - 1))
		return (0);
	while (i < (size_t)(*ret) - 1)
	{
		ent->save[i] = (*buffer)[i];
		++i;
	}
	ent->save[i] = '\0';
	ent->save = trim_entry(ent->save, in_word);
	return (1);
}

int			sent_fill(t_entry *ent)
{
	ssize_t			ret;
	char			buffer[READ_MAX + 1];

	if ((ret = read(ent->fd, buffer, READ_MAX + 1)) > 0
		&& buffer[0] != ent->end && !sub_fill(ent, &buffer, &ret))
		return (0);
	if (ret == -1)
	{
		write(2, "\033[31m42sh:\033[0m Something strange happened. ", 43);
		write(2, "To avoid all risks the shell will be stopped.\nExit\n", 51);
		return (0);
	}
	if (ret == 0)
	{
		if (ent->job && !no_job_stopped(ent->job))
			write(2, "\033[1D\033[K\n42sh: There are suspended jobs.\n", 40);
		else
		{
			if (ent->job)
				free(&(ent->job));
			write(1, "\033[1D\033[K\nexit\n", 13);
			exit(ent->exit_status);
		}
	}
	return (1);
}
