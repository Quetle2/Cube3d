NAME = CUBADO

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

ANM_SRC = 

MAIN_SRC = main.c player.c raycast.c

GNL_SRC = get_next_line_utils.c get_next_line.c

MAP_SRC = 

all: $(NAME)

run:	all
	@./CUBADO map.ber

valgrind:	all
	@valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./CUBADO map.ber

git:	fclean
	@git add .
	@git commit -m "automatico"
	@git push

clean:
	@make clean -s -C ft_printf_100
	@make clean -s -C mlx_linux

fclean:
	@make fclean -s -C ft_printf_100
	@$(RM) $(NAME)

re: fclean all

$(NAME): 
	@make -s -C ft_printf_100
	@make -s -C mlx_linux
	@$(CC) $(CFLAGS) $(addprefix Main_SRC/,$(MAIN_SRC)) $(addprefix interations/,$(ANM_SRC)) $(addprefix map_checker/,$(MAP_SRC)) $(addprefix get_next_line_100/,$(GNL_SRC)) ft_printf_100/libftprintf.a mlx_linux/libmlx_Linux.a -lXext -lX11 -o $(NAME)
