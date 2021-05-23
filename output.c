/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:59:49 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/17 15:18:09 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar(char c)
{
	count_return(0);
	write(1, &c, 1);
}

void	ft_putnbr(long long n)
{
	char c;

	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		n = n * -1;
		ft_putchar('-');
	}
	if (n / 10 != 0)
	{
		ft_putnbr(n / 10);
	}
	c = (n % 10) + '0';
	ft_putchar(c);
}

void	ft_putstr(char *str, int *currstate)
{
	int i;
	int len;

	if (str == 0)
		str = "(null)";
	len = (currstate[3] == -1) ? ft_strlen(str) : currstate[3];
	i = 0;
	while (i < len && str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	init(char flag, int *bits, int *bintab)
{
	*bits = (flag == 'x' || flag == 'X') ? 32 : 64;
	bintab[0] = 1;
	bintab[1] = 2;
	bintab[2] = 4;
	bintab[3] = 8;
	bintab[4] = 0;
}

void	ft_puthex(long long nbr, char flag)
{
	int		i;
	int		bits;
	int		bintab[5];
	int		res;
	char	*hex;

	init(flag, &bits, bintab);
	if (nbr == 0)
		return (ft_putchar('0'));
	hex = "0123456789abcdef";
	while (bits - 4 >= 0)
	{
		bits = bits - 4;
		i = 0;
		res = 0;
		while (i < 4)
		{
			res += ((nbr >> (bits + i)) & 1) * bintab[i];
			i++;
		}
		if (res != 0)
			bintab[4] = 1;
		if (bintab[4] == 1)
			ft_putchar((flag == 'X') ? ft_toupper(hex[res]) : hex[res]);
	}
}
