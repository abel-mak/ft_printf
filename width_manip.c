/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:03:30 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/19 13:13:01 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** why used tmp in putwidthbefore?
** problem case currstate[3] > 0 and currstate[2] == 1
** example currstate[3] = 4 and input 150 so output is 0150
** in currstate[0] not substract the zero it substract just 3 (150 input_len)
** but currstate[3] get used in putwidthcasedot and become 0 after
** decrementin it.
** currstate[4] has the same value we can rely on it
** but must check case currstate[4] (isastrisk) with currstate[3] (is dot).
** second cas, add 1 in case nozero and for minus printed
** in case zero it counted as input length and input is negative
*/

void		putwidthbefore(long long input, char flag, int *currstate)
{
	int		input_len;
	char	width_fill;
	int		tmp;

	if (currstate[3] == 0 && currstate[1] == 1 && flag != 's')
		currstate[1] = 0;
	width_fill = (currstate[1] == 1) ? '0' : ' ';
	input_len = inputlength(input, flag, currstate);
	if ((flag == 'd' || flag == 'i') && (int)input < 0 && (currstate[1] == 1))
	{
		currstate[5] = 1;
		ft_putchar('-');
	}
	tmp = (currstate[4] > input_len && currstate[3] == 0)
		? (currstate[4] - input_len) : 0;
	tmp += (currstate[5] == 1 && currstate[1] == 0) ? 1 : 0;
	currstate[0] = currstate[0] - (input_len + tmp);
	while (currstate[0] > 0)
	{
		ft_putchar(width_fill);
		currstate[0]--;
	}
}

/*
** why use tmp in putwidthcasedot_sub?
** if input negtive add 1 cause it's not considered in inputlength
** because it's dotcase
*/

void		putwidthdot_sub(long long input, char flag, int *currstate, int le)
{
	int tmp;
	int input_len;

	input_len = le;
	tmp = 0;
	if (flag == 'd' || flag == 'i')
		tmp = ((int)input < 0) ? currstate[3] + 1 : currstate[3];
	else if (flag != 'x' && flag != 'X' && flag != 'p' && flag != 'u')
		tmp = (input < 0) ? currstate[3] + 1 : currstate[3];
	else
		tmp = currstate[3];
	currstate[0] = currstate[0] - (tmp + input_len);
	while (currstate[0] > 0)
	{
		ft_putchar(' ');
		currstate[0]--;
	}
}

/*
** in case %-10.4d we have any idea how length would output after
** precision cause we lost currstate[3] in this function
** currstate[3] means there is 0 so print - before zeros and set
** currstate[5] to 1
*/

void		putwidthcasedot(long long input, char flag, int *currstate)
{
	int input_len;

	if (flag == 's' && currstate[2] == 0)
		return (putwidthbefore(input, flag, currstate));
	else if (flag == 's')
		return ;
	input_len = inputlength(input, flag, currstate);
	currstate[4] = currstate[3];
	currstate[3] = (currstate[3] > input_len) ? currstate[3] - input_len : 0;
	if (currstate[0] > 0 && currstate[2] == 0)
		putwidthdot_sub(input, flag, currstate, input_len);
	if ((flag == 'd' || flag == 'i') && (int)input < 0 && currstate[3] > 0)
	{
		currstate[5] = 1;
		ft_putchar('-');
	}
	if (currstate[3] > 0 && isnumflag(flag) == 1)
	{
		while (currstate[3] > 0)
		{
			ft_putchar('0');
			currstate[3]--;
		}
	}
}

long long	checksign(long long input, int *currstate)
{
	if (currstate[5] == 1 && input == -2147483648)
		return (input * -1);
	else if (currstate[5] == 1 && (int)input < 0)
		return ((int)input * -1);
	return ((int)input);
}

/*
** why used tmp in flag_manip?
** in case = 0 means there's dot it's set to zero
** so don't print that ("%.d" or ("%.*d", 0))
** in case = -1 means thers's no dot so print print 0
** in case > 0 means there's dot and it's not set zero so print zero
** i used currstate[4] because i lose currstate[3] in printcasedot
*/

void		flag_manip(long long input, char flag, int *currstate)
{
	int tmp;

	if (currstate[2] == 0 && (currstate[3] == -1 || currstate[3] == 0))
		putwidthbefore(input, flag, currstate);
	else if (currstate[3] > 0)
		putwidthcasedot(input, flag, currstate);
	tmp = currstate[4] + currstate[3];
	if (flag == 's')
		ft_putstr((char*)input, currstate);
	else if ((flag == 'd' || flag == 'i') && (tmp != 0 || input != 0))
		ft_putnbr(checksign((int)input, currstate));
	else if (flag == 'c')
		ft_putchar((char)input);
	else if (flag == 'u' && (tmp != 0 || input != 0))
		ft_putnbr((unsigned int)input);
	else if ((flag == 'x' || flag == 'X') && (tmp != 0 || input != 0))
		ft_puthex((int)input, flag);
	else if (flag == 'p')
	{
		putzerox('p');
		if (tmp != 0 || input != 0)
			ft_puthex(input, flag);
	}
	if (currstate[2] == 1)
		putwidthbefore(input, flag, currstate);
}
