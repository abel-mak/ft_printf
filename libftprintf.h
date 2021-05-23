/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:12:53 by abel-mak          #+#    #+#             */
/*   Updated: 2019/12/17 19:41:36 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

enum	e_state
{
	e_state_start,
	e_state_percent,
	e_state_zero,
	e_state_minus,
	e_state_digit,
	e_state_dot,
	e_state_flag
};
int				ft_toupper(int c);
size_t			ft_strlen(char const *str);
int				count_return(int init);
void			ft_putchar(char c);
void			ft_putnbr(long long n);
int				isflag(int c);
int				isnumflag(int c);
int				inputlength_dec_uns(long long input, char flag, int *currstate);
int				inputlength_hex(long long input, int *currstate);
int				inputlength_pointer(long long input, int *currstate);
int				inputlength(long long input, char flag, int *currstate);
void			putwidthbefore(long long input, char flag, int *currstate);
void			ft_putstr(char *str, int *currstate);
void			init(char flag, int *bits, int *bintab);
void			ft_puthex(long long nbr, char flag);
void			putwidthcasedot_sub(long long input, char flag,
	int *currstate, int le);
void			putwidthcasedot(long long input, char flag, int *currstate);
void			putzerox(char flag);
long long		checksign(long long input, int *currstate);
void			flag_manip(long long input, char flag, int *currstate);
enum e_state	start(int c, int *currstate);
enum e_state	percent_astdotcase(int c, int *currstate);
enum e_state	percent(int c, int *currstate);
enum e_state	zero_astcase(int c, int *currstate);
enum e_state	zero(int c, int *currstate);
enum e_state	digit(int c, int *currstate);
enum e_state	dot(int c, int *currstate);
enum e_state	minus_astdotcase(int c, int *currstate);
enum e_state	minus(int c, int *currstate);
enum e_state	falsepercent(int *currstate);
enum e_state	resetstate(int *currstate);
enum e_state	state_manip(int c, enum e_state state, int *currstate);
int				ft_printf(const char *str, ...);

#endif
