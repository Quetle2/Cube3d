NAME = cub3D

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

SRC_MOVE = movimentounderscoresensual/player_helper.c movimentounderscoresensual/player.c \
	movimentounderscoresensual/pacima.c movimentounderscoresensual/padireita.c \
	movimentounderscoresensual/paesquerda.c movimentounderscoresensual/pabaixo.c

SRC_FREE = free_and_error/error.c free_and_error/free_utils.c free_and_error/free.c

SRC_PARSE = parsing/check_map_utils.c parsing/check_map.c parsing/create_map_utils.c \
	parsing/create_map.c parsing/get_data_utils.c parsing/get_data.c \
	parsing/parse_utils.c parsing/parse.c

SRC_RENDER = render/bolas.c render/draw.c render/draw2.c render/interagir.c \
	render/raycast_utils.c render/raycast.c render/utils.c

MAIN_SRC = main.c init.c $(SRC_MOVE) $(SRC_FREE) $(SRC_PARSE) $(SRC_RENDER)

GNL_SRC = get_next_line_utils.c get_next_line.c

all: $(NAME)
run:	all
	@./cub3d maps/map1.cub

valgrind:	all
	@valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./CUBADO map.ber

git:	fclean
	@git add .
	@git commit -m "automatico"
	@git push

clean:
	@make clean -s -C ft_printf_100
#	@make clean -s -C mlx_linux

fclean: clean
	@make fclean -s -C ft_printf_100
	@$(RM) $(NAME)

re: fclean all

$(NAME): 
	@make -s -C ft_printf_100
#	@make -s -C mlx_linux
	@$(CC) $(CFLAGS) $(addprefix Main_SRC/,$(MAIN_SRC)) $(addprefix get_next_line_100/,$(GNL_SRC)) ft_printf_100/libftprintf.a mlx_linux/libmlx_Linux.a -lXext -lX11 -lm -o $(NAME)
