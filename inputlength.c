/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputlength.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:54:39 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/17 12:39:43 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	putzerox(char flag)
{
	if (flag == 'p')
	{
		ft_putchar('0');
		ft_putchar('x');
	}
}

/*
** input == 0 and currstate[3] == 0 don't count because it's not gonna print 0
*/

int		inputlength_dec_uns(long long input, char flag, int *currstate)
{
	int input_len;

	input_len = 0;
	if ((flag != 'u' && (int)input < 0) && currstate[3] <= 0)
		input_len = 1;
	else if (input == 0 && currstate[3] != 0)
		input_len = 1;
	while (input != 0)
	{
		input = (flag != 'u') ? (int)input / 10 : (unsigned int)input / 10;
		input_len++;
	}
	return (input_len);
}

int		inputlength_hex(long long input, int *currstate)
{
	int input_len;

	input_len = 0;
	input = (unsigned int)input;
	if (input == 0 && currstate[3] != 0)
		input_len = 1;
	while (input != 0)
	{
		input = input / 16;
		input_len++;
	}
	return (input_len);
}

int		inputlength_pointer(long long input, int *currstate)
{
	int					input_len;
	unsigned long long	llu_input;

	llu_input = (unsigned long long)input;
	input_len = 0;
	if (llu_input == 0 && currstate[3] != 0)
		input_len = 1;
	input_len += 2;
	while (llu_input != 0)
	{
		llu_input = llu_input / 16;
		input_len++;
	}
	return (input_len);
}

/*
** if (input == 0) output is (null) has 6 characters
*/

int		inputlength(long long input, char flag, int *currstate)
{
	int input_len;

	input_len = 0;
	if (flag == 'd' || flag == 'i' || flag == 'u')
		input_len = inputlength_dec_uns(input, flag, currstate);
	if (flag == 'x' || flag == 'X')
		input_len = inputlength_hex(input, currstate);
	if (flag == 'p')
		input_len = inputlength_pointer(input, currstate);
	if (flag == 's')
	{
		input_len = (input != 0) ? ft_strlen((char*)input) : 6;
		input_len = (currstate[3] == -1 || currstate[3] > input_len)
			? input_len : currstate[3];
	}
	if (flag == 'c')
		input_len = 1;
	return (input_len);
}
