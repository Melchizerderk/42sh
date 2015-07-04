/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 17:40:18 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/10 00:27:28 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

char		*ft_strdup(char *str)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if ((tmp = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = '\0';
	return (tmp);
}

int			ft_atoi(const char *s)
{
	int		res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r'
			|| s[i] == '\v' || s[i] == '\f' || s[i] == '\n')
		++i;
	if (s[i] == '-' || s[i] == '+')
	{
		sign = ((s[i] == '-') ? -1 : 1);
		++i;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += s[i] - '0';
		++i;
	}
	return (res * sign);
}
