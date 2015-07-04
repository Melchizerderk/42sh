/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:41:54 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/10 00:28:16 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

size_t	ft_strlen(char *str)
{
	char	*origin;

	origin = str;
	if (str == (void *)0)
		return (0);
	while (*str != '\0')
		++str;
	return ((size_t)(str - origin));
}

void	*ft_memset(void *s, int c, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	tmp = (char *)s;
	while (i < len)
	{
		tmp[i] = (char)c;
		++i;
	}
	return ((void *)tmp);
}

int		ft_strncmp(char *s1, char *s2, size_t len)
{
	if (*s1 != *s2 && (ft_strlen(s1) == 0 || ft_strlen(s2) == 0))
		return (-1);
	if (*s1 == *s2 && ft_strlen(s1) == 0)
		return (0);
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0' && len > 1)
	{
		++s1;
		++s2;
		--len;
	}
	if (len == 1)
	{
		if (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		{
			++s1;
			++s2;
			--len;
		}
	}
	if (*s2 == '\0' && len == 0)
		return (0);
	return ((int)(*s1 - *s2));
}

char	*ft_strjoin(char *str1, char *str2, char c)
{
	char	*tmp;
	size_t	len[3];

	len[0] = 0;
	len[1] = ft_strlen(str1);
	len[2] = ft_strlen(str2);
	if ((tmp = (char *)malloc(sizeof(char) * (len[1] + len[2] + 2))) == NULL)
	{
		write(2, "Error in ft_strjoin\n", 20);
		return (NULL);
	}
	while (len[0] < len[1])
	{
		tmp[len[0]] = str1[len[0]];
		++(len[0]);
	}
	tmp[len[0]] = c;
	++(len[0]);
	while (len[0] < len[1] + len[2] + 1)
	{
		tmp[len[0]] = str2[len[0] - len[1] - 1];
		++(len[0]);
	}
	tmp[len[0]] = '\0';
	return (tmp);
}

void	ft_putnbr_off_t(off_t n, pid_t pid)
{
	off_t	decim;
	char	c;

	decim = 1;
	while ((n / decim) > 9)
		decim *= 10;
	while (decim > 0)
	{
		c = (n / decim) % 10 + '0';
		write(pid, &c, 1);
		decim /= 10;
	}
}
