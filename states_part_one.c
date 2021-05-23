/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_part_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:50:10 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/19 13:23:08 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

enum e_state	start(int c, int *currstate)
{
	if (c == '%')
		return (e_state_percent);
	else
		ft_putchar(c);
	return (resetstate(currstate));
}

/*
**(c == '*' && currstate[4] < 0)
*/

enum e_state	percent_astdotcase(int c, int *currstate)
{
	if (c == '.')
	{
		return (e_state_dot);
	}
	else if (c == '*' && currstate[4] >= 0)
	{
		currstate[0] = currstate[4];
		currstate[4] = 0;
		return (e_state_digit);
	}
	else
	{
		currstate[2] = 1;
		currstate[0] = -1 * currstate[4];
		currstate[4] = 0;
		return (e_state_minus);
	}
}

enum e_state	percent(int c, int *currstate)
{
	if (isflag(c) == 1)
		return (e_state_flag);
	else if (c == '0')
	{
		currstate[1] = 1;
		return (e_state_zero);
	}
	else if (c > '0' && c <= '9')
	{
		currstate[0] = currstate[0] * 10 + (c - '0');
		return (e_state_digit);
	}
	else if (c == '-')
	{
		currstate[2] = 1;
		return (e_state_minus);
	}
	else if (c == '.' || c == '*')
		return (percent_astdotcase(c, currstate));
	else
	{
		ft_putchar(c);
		return (resetstate(currstate));
	}
}

enum e_state	zero_astcase(int c, int *currstate)
{
	if (c == '*' && currstate[4] >= 0)
	{
		currstate[0] = currstate[4];
		currstate[4] = 0;
		return (e_state_zero);
	}
	else if (c == '*' && currstate[4] < 0)
	{
		currstate[0] = currstate[4] * -1;
		currstate[4] = 0;
		currstate[1] = 0;
		currstate[2] = 1;
		return (e_state_zero);
	}
	else
		return (falsepercent(currstate));
}

enum e_state	zero(int c, int *currstate)
{
	if (isflag(c) == 1)
		return (e_state_flag);
	else if (c == '0')
		return (e_state_zero);
	else if (c == '.')
		return (e_state_dot);
	else if (c == '-')
	{
		currstate[2] = 1;
		currstate[1] = 0;
		return (e_state_minus);
	}
	else if (c == '*' || c == '%')
		return (zero_astcase(c, currstate));
	else if (c > '0' && c <= '9')
	{
		currstate[0] = currstate[0] * 10 + (c - '0');
		return (e_state_digit);
	}
	else
	{
		putwidthbefore(1, 'd', currstate);
		ft_putchar(c);
		return (resetstate(currstate));
	}
}
