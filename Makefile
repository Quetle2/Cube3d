# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marada <marada@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 13:59:27 by miandrad          #+#    #+#              #
#    Updated: 2026/01/12 17:57:57 by marada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

ANM_SRC = 

MAIN_SRC = main.c

GNL_SRC = get_next_line_utils.c get_next_line.c

MAP_SRC = 

all: $(NAME)

run:	all
	@./so_long map.ber

valgrind:	all
	@valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./so_long map.ber

clean:
	@make clean -s -C ft_printf_100
	@make clean -s -C mlx_linux

fclean:
	@make fclean -s -C ft_printf_100
	@$(RM) so_long

re: fclean all

$(NAME): 
	@make -s -C ft_printf_100
	@make -s -C mlx_linux
	@$(CC) $(CFLAGS) $(addprefix Main_SRC/,$(MAIN_SRC)) $(addprefix interations/,$(ANM_SRC)) $(addprefix map_checker/,$(MAP_SRC)) $(addprefix get_next_line_100/,$(GNL_SRC)) ft_printf_100/libftprintf.a mlx_linux/libmlx_Linux.a -lXext -lX11 -o $(NAME)
