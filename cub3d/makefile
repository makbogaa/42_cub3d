NAME=cub3d
CC=cc
CFLAGS= -Wall -Wextra -Werror
SRC= src/file_extension.c src/string_utils.c src/map_parse.c src/map_parse_two.c src/color_parse.c src/player.c main.c src/game/start.c src/game/events.c src/game/event_func.c src/game/free_game.c src/game/map.c src/game/draw.c src/game/raycaster.c src/game/texture.c
OBJ=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@


all:$(NAME)

$(NAME):$(OBJ)
	make -C src/game/minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) src/game/minilibx-linux/libmlx_Linux.a -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

run:$(NAME)
	valgrind --track-origins=yes --leak-check=full -s ./$(NAME) $(map)
clean:
	make clean -C src/game/minilibx-linux
	rm -f $(OBJ)
fclean:clean
	rm -f $(NAME)
re:fclean all
	make re -C src/game/minilibx-linux

.PHONY: all clean fclean re