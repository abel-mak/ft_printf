/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:17:15 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/19 11:19:25 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - ('a' - 'A'));
	}
	return (c);
}

size_t	ft_strlen(char const *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		count_return(int init)
{
	static int	i;
	int			res;

	i++;
	res = i;
	if (init == 1)
		i = 0;
	return (res);
}

int		isflag(int c)
{
	char	*flags;
	int		i;

	flags = "cspdiuxX";
	i = 0;
	while (flags[i] != '\0')
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		isnumflag(int c)
{
	char	*numflags;
	int		i;

	numflags = "diuxX";
	i = 0;
	while (numflags[i] != '\0')
	{
		if (numflags[i] == c)
			return (1);
		i++;
	}
	return (0);
}
