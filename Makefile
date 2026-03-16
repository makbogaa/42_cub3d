NAME=cub3D
CC=cc
CFLAGS= -Wall -Wextra -Werror
SRC= src/parse/file_extension.c \
src/parse/string_utils.c \
src/parse/read_map.c \
src/parse/read_map_two.c \
src/parse/read_map_three.c \
src/parse/parse_map.c \
src/parse/parse_map_two.c \
src/parse/parse_map_three.c \
src/parse/color_and_texture_parse.c \
src/game/start.c \
src/game/events.c \
src/game/event_func.c \
src/game/free_game.c \
src/game/draw_three_d.c\
src/game/draw_texture.c\
src/game/get_xpm_files.c\
main.c 
OBJ=$(SRC:.c=.o)


all:$(NAME)

$(NAME):$(OBJ)
	make -C src/game/minilibx-linux
	make -C src/Libft
	$(CC) $(CFLAGS) $(OBJ) src/Libft/libft.a src/game/minilibx-linux/libmlx_Linux.a -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

run:$(NAME)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(NAME) $(map)
clean:
	make clean -C src/game/minilibx-linux
	make clean -C src/Libft
	rm -f $(OBJ)
fclean:clean
	make fclean -C src/Libft
	rm -f $(NAME)
re:fclean all
	make re -C src/game/minilibx-linux
	make re -C src/Libft
.PHONY: all clean fclean re