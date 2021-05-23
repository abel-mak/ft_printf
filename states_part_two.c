/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_part_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:52:50 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/19 13:15:21 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

enum e_state	digit(int c, int *currstate)
{
	if (isflag(c) == 1)
		return (e_state_flag);
	else if (c >= '0' && c <= '9')
	{
		currstate[0] = currstate[0] * 10 + (c - '0');
		return (e_state_digit);
	}
	else if (c == '.')
		return (e_state_dot);
	else if (c == '-')
	{
		currstate[2] = 1;
		return (e_state_minus);
	}
	else if (c == '%')
		return (falsepercent(currstate));
	else
	{
		putwidthbefore(1, 'd', currstate);
		ft_putchar(c);
		return (resetstate(currstate));
	}
}

enum e_state	dot(int c, int *currstate)
{
	currstate[3] = (currstate[3] == -1) ? 0 : currstate[3];
	if (isflag(c) == 1)
		return (e_state_flag);
	if (c == '*')
	{
		currstate[3] = (currstate[4] < 0) ? -1 : currstate[4];
		return (e_state_digit);
	}
	else if (c >= '0' && c <= '9')
	{
		currstate[3] = currstate[3] * 10 + (c - '0');
		return (e_state_dot);
	}
	else if (c == '%')
		return (falsepercent(currstate));
	else
	{
		putwidthbefore(1, 'd', currstate);
		ft_putchar(c);
		return (resetstate(currstate));
	}
}

enum e_state	minus_astdotcase(int c, int *currstate)
{
	if (c == '*')
	{
		currstate[0] = (currstate[4] < 0) ? currstate[4] * -1 : currstate[4];
		currstate[4] = 0;
		return (e_state_minus);
	}
	else
		return (e_state_dot);
}

enum e_state	minus(int c, int *currstate)
{
	if (isflag(c) == 1)
		return (e_state_flag);
	else if (c == '-')
		return (e_state_minus);
	else if (c == '0')
	{
		currstate[1] = 0;
		return (e_state_minus);
	}
	else if (c == '.' || c == '*')
		return (minus_astdotcase(c, currstate));
	else if (c > '0' && c <= '9')
	{
		currstate[0] = currstate[0] * 10 + (c - '0');
		return (e_state_digit);
	}
	else if (c == '%')
		return (falsepercent(currstate));
	else
	{
		ft_putchar(c);
		putwidthbefore(1, 'd', currstate);
		return (resetstate(currstate));
	}
}

enum e_state	falsepercent(int *currstate)
{
	if (currstate[0] > 0 && currstate[2] == 0)
	{
		putwidthbefore(1, 'd', currstate);
	}
	ft_putchar('%');
	if (currstate[0] > 0 && currstate[2] != 0)
	{
		putwidthbefore(1, 'd', currstate);
	}
	return (resetstate(currstate));
}
