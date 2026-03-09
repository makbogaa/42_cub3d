/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:00:55 by mdalkili          #+#    #+#             */
/*   Updated: 2026/03/01 21:01:43 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_print(char *msg)
{
	printf("%s", msg);
	return (0);
}

static int	init_player(t_game *game, t_player *player)
{
	game->player = player;
	memset(game->player->keys, 0, sizeof(game->player->keys));
	game->player->rays = malloc(sizeof(t_ray) * game->max_ray);
	if (!game->player->rays)
	{
		perror("malloc:");
		return (0);
	}
	game->ray_color = 0xFF00FF;
	game->player->move = 1;
	game->player->state = 0;
	game->player->color = 0xFF0FF0;
	return (1);
}

static void	init_map(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->start[0] = 0;
	map->order_number = 3;
	map->orders[0] = 0;
	map->orders[1] = 0;
	map->orders[2] = 0;
	map->side_xpm_files[0] = NULL;
	map->side_xpm_files[1] = NULL;
	map->side_xpm_files[2] = NULL;
	map->side_xpm_files[3] = NULL;
	map->side_xpm_files[4] = NULL;
	map->xpm_height = 64;
	map->xpm_width = 64;
	map->f.r = -1;
	map->c.r = -1;
	map->matrix = NULL;
	map->matrix_current_row = 0;
	map->row_count = 0;
	map->map_ended = 0;
	map->read_vars.total_buffer = 1;
	map->read_vars.buffer = NULL;
	map->read_vars.temp[1] = 0;
}

static int	init_game(t_game *game, t_map *map, t_player *player)
{
	game->map = map;
	init_map(map);
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->window_data.img = NULL;
	game->window_data.addr = NULL;
	game->width = 1200;
	game->height = 700;
	game->max_ray = 50;
	if (!init_player(game, player))
		return (0);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_print("Mlx init error\n"));
	game->mlx_win = mlx_new_window(game->mlx,
			game->width, game->height, "Cub3D");
	if (!game->mlx_win)
		return (error_print("Mlx window create error\n"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_player	player;

	if (argc != 2)
	{
		printf("Argument count must be one\n");
		return (1);
	}
	if (!extension_control(argv[1]) || !file_control(argv[1], &map))
		return (1);
	if (!content_exist_control(argv[1], &map))
		return (1);
	if (init_game(&game, &map, &player))
	{
		if (!read_and_parse_map(&map) || !order_control(&map))
			return (free_game(&game), 1);
		start_player(&game);
		if (!map_control(&game))
			return (free_game(&game), 1);
		start_game(&game);
	}
	free_game(&game);
	return (0);
}
