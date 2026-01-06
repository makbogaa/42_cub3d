#include "cub3d.h"

static void init_map(t_map *map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->ea_path = NULL;
	map->we_path = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->matrix = NULL;
	map->matrix_current_row = 0;
}

static void	init_game(t_game *game, t_map *map, t_player *player)
{
	int i;

	game->map = map;
	init_map(map);
	game->width = 1920;
	game->height = 1080;
	game->cell_size = 64;
	game->max_ray = 100;
	game->player = player;
	game->player->rays = malloc(sizeof(t_ray) * game->max_ray);
	if(!game->player->rays)
		exit(EXIT_FAILURE);
	game->ray_color = 0xFF00FF;
	game->player->state = 0;
	game->player->size = 32;
	game->player->angle = 0;
	game->player->fov = 60 * (acos(-1.0)/180);
	printf("%f",game->player->fov);
	game->player->color = 0xFF0000;
	i = 0;
	while (i < 65536)
		game->player->keys[i++] = 0;
}

int main(int argc,char **argv)
{
	t_game		game;
	t_map		map;
	t_player	player;

	if(argc != 2)
		return (1);
	if(!extension_control(argv[1]))
		return (1);
	init_game(&game, &map, &player);
	read_and_parse_map(argv[1], &map);
	find_player_position(&game);
	start_game(&game);
	free_game(&game);
	return (0);
}