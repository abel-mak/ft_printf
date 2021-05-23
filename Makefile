# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/16 18:24:55 by abel-mak          #+#    #+#              #
#    Updated: 2019/12/19 13:55:31 by abel-mak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRC=ft_printf.c inputlength.c output.c states_part_one.c states_part_two.c \
	utils.c width_manip.c

OBJECTS= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c
	gcc -c -Wall -Wextra -Werror $<

clean:
	rm -rf $(OBJECTS)

fclean:clean
	rm -rf $(NAME)

re: fclean all
