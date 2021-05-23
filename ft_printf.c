/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:29:21 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/19 11:47:44 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

enum e_state	resetstate(int *currstate)
{
	currstate[0] = 0;
	currstate[1] = 0;
	currstate[2] = 0;
	currstate[3] = -1;
	currstate[4] = 0;
	currstate[5] = 0;
	return (e_state_start);
}

enum e_state	state_manip(int c, enum e_state state, int *currstate)
{
	enum e_state newstate;

	newstate = e_state_start;
	if (state == e_state_start)
		newstate = start(c, currstate);
	else if (state == e_state_percent)
		newstate = percent(c, currstate);
	else if (state == e_state_zero)
		newstate = zero(c, currstate);
	else if (state == e_state_digit)
		newstate = digit(c, currstate);
	else if (state == e_state_dot)
		newstate = dot(c, currstate);
	else if (state == e_state_minus)
		newstate = minus(c, currstate);
	return (newstate);
}

/*
**currstate = {iswidth, iszero, isminus, isdot, isastrisk, isprintminus}
*/

int				ft_printf(const char *str, ...)
{
	int				i;
	va_list			ag;
	enum e_state	state;
	int				currstate[6];

	resetstate(currstate);
	state = e_state_start;
	va_start(ag, str);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '*' && state != e_state_start)
			currstate[4] = (int)va_arg(ag, long long);
		state = state_manip(str[i], state, currstate);
		if (state == e_state_flag)
		{
			state = e_state_start;
			flag_manip(va_arg(ag, long long), str[i], currstate);
			resetstate(currstate);
		}
		i++;
	}
	va_end(ag);
	return (count_return(1) - 1);
}
